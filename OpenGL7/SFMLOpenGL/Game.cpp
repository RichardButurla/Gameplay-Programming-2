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
	float color[4];
	float texel[2];
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

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
vsid,		//Vertex Shader ID
fsid,		//Fragment Shader ID
progID,		//Program ID
vao = 0,	//Vertex Array ID
vbo[1],		// Vertex Buffer ID
positionID, //Position ID
colorID,	// Color ID
to,			// Texture ID 1 to 32
textureID,	//Texture ID
texelID;	// Texel ID


//const string filename = "texture.tga";
//const string filename = "cube.tga";

const string filename = "cube.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA


unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	int colorIndex = 0;

	glewInit();

	for (int i = 0; i < 24; i++)
	{

		vertex[i].coordinate[0] = vertexes[i].x;
		vertex[i].coordinate[1] = vertexes[i].y;
		vertex[i].coordinate[2] = vertexes[i].z;

	}

	//Front Face
	vertex[0].texel[0] = 0.25f;
	vertex[0].texel[1] = 0.5f;

	vertex[1].texel[0] = 0.5f;
	vertex[1].texel[1] = 0.5f;

	vertex[2].texel[0] = 0.5f;
	vertex[2].texel[1] = 0.25f;

	vertex[3].texel[0] = 0.25f;
	vertex[3].texel[1] = 0.25f;

	//Right Face
	vertex[4].texel[0] = 0.5f;
	vertex[4].texel[1] = 0.5f;

	vertex[5].texel[0] = 0.75f;
	vertex[5].texel[1] = 0.5f;

	vertex[6].texel[0] = 0.75f;
	vertex[6].texel[1] = 0.25f;

	vertex[7].texel[0] = 0.5f;
	vertex[7].texel[1] = 0.25f;

	//Back Face
	vertex[8].texel[0] = 0.75f;
	vertex[8].texel[1] = 0.5f;

	vertex[9].texel[0] = 1.f;
	vertex[9].texel[1] = 0.5f;

	vertex[10].texel[0] = 1.f;
	vertex[10].texel[1] = 0.25f;

	vertex[11].texel[0] = 0.75f;
	vertex[11].texel[1] = 0.25f;

	//Left Face
	vertex[12].texel[0] = 0.0f;
	vertex[12].texel[1] = 0.5f;

	vertex[13].texel[0] = 0.25f;
	vertex[13].texel[1] = 0.5f;

	vertex[14].texel[0] = 0.25f;
	vertex[14].texel[1] = 0.25f;

	vertex[15].texel[0] = 0.f;
	vertex[15].texel[1] = 0.25f;

	//Top Face
	vertex[16].texel[0] = 0.25f;
	vertex[16].texel[1] = 0.25f;

	vertex[17].texel[0] = 0.5f;
	vertex[17].texel[1] = 0.25f;

	vertex[18].texel[0] = 0.5f;
	vertex[18].texel[1] = 0.f;

	vertex[19].texel[0] = 0.25f;
	vertex[19].texel[1] = 0.f;

	//Back Face
	vertex[20].texel[0] = 0.25f;
	vertex[20].texel[1] = 0.75f;

	vertex[21].texel[0] = 0.5f;
	vertex[21].texel[1] = 0.75f;

	vertex[22].texel[0] = 0.5f;
	vertex[22].texel[1] = 0.5f;

	vertex[23].texel[0] = 0.25f;
	vertex[23].texel[1] = 0.5f;



	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 24, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangleIndexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	////////////////////////////////////
	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = readFromFile("shader.vert");

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
	const char* fs_src = readFromFile("shader.frag");

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

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		std::cout << ("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
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

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, to);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (float*)NULL + 3);
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(7 * sizeof(float)));

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);


	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

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
	stbi_image_free(img_data); //Free image
}

const char* readFromFile(std::string t_fileName)
{
	std::ifstream file(t_fileName);
	std::string string;
	std::string fileText;
	char* src = nullptr;
	bool readVersionLine = false;

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::getline(file, string);
			fileText += string;

			//if we havent read the shader version file add a newline and return carriage char
			if (readVersionLine == false) {
				readVersionLine = true;
				fileText += "\n\r";
			}
		}
		src = new char[fileText.size() + 1];
		std::strcpy(src, fileText.c_str());

		file.close();
	}
	return src;
}
