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
	isRunning = true;
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x /
		window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);

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

