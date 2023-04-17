#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
			processEvents(event);
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[MAX_CUBE_FACES * 4];
GLubyte triangleIndexes[]
{
	// Front face
	0, 1, 2,
	2, 3, 0,
	// Right face
	4, 5, 6,
	6, 7, 4,
	// Back face
	8, 9, 10,
	10, 11, 8,
	// Left face
	12, 13, 14,
	14, 15, 12,
	// Top face
	16, 17, 18,
	18, 19, 16,
	// Bottom face
	20, 21, 22,
	22, 23 ,20
};

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;
/* Variable to hold the VBO identifier and shader data */
GLuint vsid, //Vertex Shader ID
fsid, //Fragment Shader ID
progID, //Program ID
//vbo = 1, // Vertex Buffer ID
positionID, //Position ID
colorID; // Color ID


void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	int colorIndex = 0;

	glewInit();

	for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
	{
		if (i % 4 == 0)
		{
			colorIndex++;
		}
		vertex[i].coordinate[0] = vertexes[i].x;
		vertex[i].coordinate[1] = vertexes[i].y;
		vertex[i].coordinate[2] = vertexes[i].z;

		/*vertex[i].color[0] = m_cubeColors[colorIndex].x;
		vertex[i].color[1] = m_cubeColors[colorIndex].y;
		vertex[i].color[2] = m_cubeColors[colorIndex].z;*/
	}
	
	



	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 32, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangleIndexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	////////////////////////////////////
	/* Vertex Shader which would normally be loaded from an external file */
	std::ifstream vertexFile("sharder.vert");
	const char* vs_src = readFromFile(vertexFile);

	//const char* vs_src = "#version 400\n\r"
	//	"in vec4 sv_position;"
	//	"in vec4 sv_color;"
	//	"out vec4 color;"
	//	"void main() {"
	//	"	color = sv_color;"
	//	"	gl_Position = sv_position;"
	//	"}"; //Vertex Shader Src

	std::cout << "\nSetting Up Vertex Shader";

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		std::cout << ("\nVertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		std::cout << ("\nERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"in vec4 color;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = color + vec4(0.0f, 0.0f, 0.5f, 0.5f);"
		"}"; //Fragment Shader Src

	std::cout << ("\nSetting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		std::cout << ("\nFragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		std::cout << ("\nERROR: Fragment Shader Compilation Error");
	}

	std::cout << ("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		std::cout << ("\nShader Linked");
	}
	else
	{
		std::cout << ("\nERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}


void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}
}

void Game::render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 24, vertex, GL_STATIC_DRAW);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)NULL + 3);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);


	glDrawElements(GL_TRIANGLES, 32, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::processEvents(sf::Event event)
{
	if (event.type == sf::Event::Closed)
	{
		isRunning = false;
	}
	MyVector3 moveVector{ 0,0,0 };
	float rotation = 1.1f;

	switch (event.type)
	{
	case sf::Event::Closed:
		window.close();
		break;
	case sf::Event::KeyPressed:


		MyMatrix xRotation;
		MyMatrix yRotation;
		MyMatrix zRotation;
		MyMatrix scaleMatrix;

		switch (event.key.code)
		{
		case sf::Keyboard::T:
			yRotation = MyMatrix::rotationAntiClockwiseY(rotation);

			for (int i = 0; i < 6; i++)
			{

				for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
				{
					MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2]};
					point = yRotation * point;
					vertex[i].coordinate[0] = point.x;
					vertex[i].coordinate[1] = point.y;
					vertex[i].coordinate[2] = point.z;
				}

			}

			break;
		case sf::Keyboard::Y:
			yRotation = MyMatrix::rotationAntiClockwiseY(-rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
				{
					MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
					point = yRotation * point;
					vertex[i].coordinate[0] = point.x;
					vertex[i].coordinate[1] = point.y;
					vertex[i].coordinate[2] = point.z;
				}

			}
			break;

		case sf::Keyboard::G:
			xRotation = MyMatrix::rotationAntiClockwiseX(rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
				{
					MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
					point = xRotation * point;
					vertex[i].coordinate[0] = point.x;
					vertex[i].coordinate[1] = point.y;
					vertex[i].coordinate[2] = point.z;
				}

			}
			break;

		case sf::Keyboard::H:
			xRotation = MyMatrix::rotationAntiClockwiseX(-rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
				{
					MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
					point = xRotation * point;
					vertex[i].coordinate[0] = point.x;
					vertex[i].coordinate[1] = point.y;
					vertex[i].coordinate[2] = point.z;
				}

			}
			break;
		case sf::Keyboard::V:
			zRotation = MyMatrix::rotationAntiClockwiseZ(rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
				{
					MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
					point = zRotation * point;
					vertex[i].coordinate[0] = point.x;
					vertex[i].coordinate[1] = point.y;
					vertex[i].coordinate[2] = point.z;
				}

			}
			break;
		case sf::Keyboard::B:
			zRotation = MyMatrix::rotationAntiClockwiseZ(-rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
				{
					MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
					point = zRotation * point;
					vertex[i].coordinate[0] = point.x;
					vertex[i].coordinate[1] = point.y;
					vertex[i].coordinate[2] = point.z;
				}
			}
			break;

		case sf::Keyboard::W:
			moveVector = { 0,0.1,0 };
			break;

		case sf::Keyboard::A:
			moveVector = { -0.1,0,0 };
			break;

		case sf::Keyboard::S:
			moveVector = { 0,-0.1,0 };
			break;

		case sf::Keyboard::D:
			moveVector = { 0.1,0,0 };
			break;

		case sf::Keyboard::I:
			scaleMatrix = MyMatrix::scale(0.5);
			for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
			{
				MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
				point = scaleMatrix * point;
				vertex[i].coordinate[0] = point.x;
				vertex[i].coordinate[1] = point.y;
				vertex[i].coordinate[2] = point.z;
			}
			break;

		case sf::Keyboard::O:
			scaleMatrix = MyMatrix::scale(1.5);
			for (int i = 0; i < MAX_CUBE_FACES * 4; i++)
			{
				MyVector3 point{ vertex[i].coordinate[0],vertex[i].coordinate[1],vertex[i].coordinate[2] };
				point = scaleMatrix * point;
				vertex[i].coordinate[0] = point.x;
				vertex[i].coordinate[1] = point.y;
				vertex[i].coordinate[2] = point.z;
			}
			break;

		default:
			break;
		}

		for (int i = 0; i < MAX_CUBE_FACES * 4; i ++)
		{
			vertex[i].coordinate[0] += moveVector.x;
			vertex[i].coordinate[1] += moveVector.y;
			vertex[i].coordinate[2] += moveVector.z;
		}
	}

}


void Game::unload()
{
	cout << "Cleaning up" << endl;
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
}

const char* readFromFile(std::ifstream& t_file)
{
	std::string string;
	char* src;
	if (!t_file.is_open())
	{
		while (!t_file.eof())
		{
			std::getline(t_file, string);
		}

		strcpy(src, string.c_str());
		t_file.close();		
	}
	return src;
}
