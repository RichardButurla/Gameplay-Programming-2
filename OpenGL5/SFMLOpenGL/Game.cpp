#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
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
		render();
	}

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
			for (int i = 0; i < MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3; i += 3)
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



void Game::initialize()
{
	glewInit();

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
	for (int i = 0; i < MAX_TRIANGLES; i++)
	{
		triangles[i] = i;
	}

	
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 72, vertexes, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 72, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Game::update()
{
	elapsed = clock.getElapsedTime();
	int arrayIndex = 0;
	for (int i = 0; i < MAX_TRIANGLES * 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			vertexes[i].points[j] = verticesArray[arrayIndex];
			vertexes[i].colorPoints[j] = colorsArray[arrayIndex];
			arrayIndex++;
		}
	}
	

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 12, vertexes, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

