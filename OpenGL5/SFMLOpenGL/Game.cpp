#include <Game.h>

Game::Game() : window(VideoMode(800, 600), "OpenGL")
{
	
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			processEvents(event);
		}
		update();
		draw();
	}

}

void Game::initialize()
{
	GLubyte triangles[MAX_TRIANGLES];
	myVertex vertexes[MAX_TRIANGLES * 3];
	/* Variable to hold the VBO identifier */
	GLuint vbo[1];
	GLuint index;

	//initialise arrays
	int arrayIndex = 0;
	for (int i = 0; i < MAX_TRIANGLES; i++)
	{
		for (int j = 0; j < MAX_TRIANGLE_POINTS; j++) {

			colorsArray[arrayIndex] = m_triangleColors[j].x;
			verticesArray[arrayIndex] = m_triangleCubePoints[i][j].x;

			arrayIndex++;


			colorsArray[arrayIndex] = m_triangleColors[j].y;
			verticesArray[arrayIndex] = m_triangleCubePoints[i][j].y;

			arrayIndex++;


			colorsArray[arrayIndex] = m_triangleColors[j].z;
			verticesArray[arrayIndex] = m_triangleCubePoints[i][j].z;

			arrayIndex++;

		}
	}

	int maxIndexes = MAX_TRIANGLES * MAX_TRIANGLE_POINTS;
	for (int i = 0; i < maxIndexes; i++)
	{
		vertexIndexArray[i] = i;
	}

	arrayIndex = 0;
	for (int i = 0; i < MAX_TRIANGLES * 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertexes[i].points[j] = verticesArray[arrayIndex];
			vertexes[i].colorPoints[j] = colorsArray[arrayIndex];
			arrayIndex++;
		}
	}


	glewInit();
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void Game::update()
{
	
}

void Game::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	int totalPoints = MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3;


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glVertexPointer(3, GL_FLOAT, 0, &verticesArray);
	glColorPointer(3, GL_FLOAT, 0, &colorsArray);

	glDrawArrays(GL_TRIANGLES, 0, totalPoints);

	//glDrawElements(GL_TRIANGLES, totalPoints, GL_UNSIGNED_INT, &vertexIndexArray);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	
	
	window.display();
}

void Game::processEvents(Event event)
{
	if (event.type == Event::Closed)
	{
		isRunning = false;
	}
	MyVector3 moveVector{ 0,0,0 };

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

				for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = yRotation * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
				}

			}
			
			break;
		case sf::Keyboard::Y:
			yRotation = MyMatrix::rotationAntiClockwiseY(-rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = yRotation * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
				}
				
			}
			break;

		case sf::Keyboard::G:
			xRotation = MyMatrix::rotationAntiClockwiseX(rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = xRotation * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
				}

			}
			break;

		case sf::Keyboard::H:
			xRotation = MyMatrix::rotationAntiClockwiseX(-rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = xRotation * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
				}

			}
			break;
		case sf::Keyboard::V:
			zRotation = MyMatrix::rotationAntiClockwiseZ(rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i+=3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = zRotation * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
				}

			}
			break;
		case sf::Keyboard::B:
			zRotation = MyMatrix::rotationAntiClockwiseZ(-rotation);

			for (int i = 0; i < 6; i++)
			{
				for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = zRotation * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
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
			for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
			{
				MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
				point = scaleMatrix * point;
				verticesArray[i] = point.x;
				verticesArray[i + 1] = point.y;
				verticesArray[i + 2] = point.z;
			}
			break;

		case sf::Keyboard::O:
			scaleMatrix = MyMatrix::scale(1.5);
			for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i+=3)
				{
					MyVector3 point{ verticesArray[i],verticesArray[i + 1],verticesArray[i + 2] };
					point = scaleMatrix * point;
					verticesArray[i] = point.x;
					verticesArray[i + 1] = point.y;
					verticesArray[i + 2] = point.z;
				}
			break;

		default:
			break;
		}

		for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
		{
			verticesArray[i] += moveVector.x;
			verticesArray[i + 1] += moveVector.y;
			verticesArray[i + 2] += moveVector.z;
		}
	}
	
}

void Game::unload()
{
	cout << "Cleaning up" << endl;
}

