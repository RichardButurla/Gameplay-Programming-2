#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include "MyVector3.h"
#include "Matrix.h"


using namespace std;
using namespace sf;

typedef struct
{
	float points[3];
	float colorPoints[3];
} myVertex;

class Game
{
public:
	Game();
	~Game();
	void run();
	void processEvents(Event event);
private:
	Window window;
	bool isRunning = true;
	void initialize();
	void update();
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	static const int MAX_TRIANGLES = 12;
	static const int MAX_TRIANGLE_POINTS = 3;

	GLubyte triangles[MAX_TRIANGLES];
	myVertex vertexes[MAX_TRIANGLES * 3];
	/* Variable to hold the VBO identifier */
	GLuint vbo[1];
	GLuint index;

	MyVector3 m_triangleCubePoints[MAX_TRIANGLES][MAX_TRIANGLE_POINTS]
	{
		{//front1
			{0.1,-0.1,0},
			{0.1,0.1,0},
			{0.1,0.1,0},
		},
		{//front2
			{0.1,-0.1,0},
			{0.1,0.1,0},
			{0.1,-0.1,0}
		},
		{//left1
			{-0.1,-0.1,0},
			{0.1,-0.1,0},
			{0.1,-0.1,0},
		},
		{//left2
			{-0.1,-0.1,0},
			{0.1,-0.1,0},
			{-0.1,-0.1,0}
		},
		{//right1
			{0.1,0.1,0},
			{-0.1,0.1,0},
			{-0.1,0.1,0},
		},
		{//right2
			{0.1,0.1,0},
			{-0.1,0.1,0},
			{0.1,0.1,0}
		},
		{//back1
			{-0.1,0.1,0},
			{-0.1,-0.1,0},
			{-0.1,-0.1,0},
		},
		{//back2
			{-0.1,0.1,0},
			{-0.1,-0.1,0},
			{-0.1,0.1,0}
		},
		{//top1
			{0.1,-0.1,0},
			{0.1,0.1,0},
			{-0.1,0.1,0},
		},
		{//top2
			{0.1,-0.1,0},
			{-0.1,0.1,0},
			{-0.1,-0.1,0}
		},
		{//bottom1
			{0.1,-0.1,0},
			{0.1,0.1,0},
			{-0.1,0.1,0},
		},
		{//bottom2
			{0.1,-0.1,0},
			{-0.1,0.1,0},
			{-0.1,-0.1,0}
		},

	};

	MyVector3 m_triangleColors[MAX_TRIANGLE_POINTS]
	{
		{1.0f, 0.0f, 0.0f},//V0(red)
		{0.0f, 1.0f, 0.0f}, //V1(green)
		{0.0f, 0.0f, 1.0f}, //V2(blue)
	};

	float verticesArray[MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3];
	float colorsArray[MAX_TRIANGLES * MAX_TRIANGLE_POINTS * 3];
	unsigned int vertexIndexArray[MAX_TRIANGLES * MAX_TRIANGLE_POINTS];


	float rotation = 0.5f;
};