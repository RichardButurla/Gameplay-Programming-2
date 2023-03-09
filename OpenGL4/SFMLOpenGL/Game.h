#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <gl/GL.h>
#include <gl/GLU.h>

#include "MyVector3.h"
#include "Matrix.h"

using namespace std;
using namespace sf;



class Game
{
public:
	Game();
	~Game();
	void run();
private:
	Window window;
	bool isRunning = false;
	void initialize();
	void update();
	void draw();
	void processEvents(Event event);
	void unload();

	float rotation = 0.5f;
	static const int MAX_TRIANGLES = 12;
	static const int MAX_TRIANGLE_POINTS = 3;

	MyVector3 m_triangleCubePoints[MAX_TRIANGLES][MAX_TRIANGLE_POINTS]
	{
		{//front1
			{1,0,-5},
			{1,1,-5},
			{1,1,-6},
		},
		{//front2
			{1,0,-5},
			{1,1,-6},
			{1,0,-6}
		},
		{//left1
			{0,0,-5},
			{1,0,-5},
			{1,0,-6},
		},
		{//left2
			{0,0,-5},
			{1,0,-6},
			{0,0,-6}
		},
		{//right1
			{1,1,-5},
			{0,1,-5},
			{0,1,-6},
		},
		{//right2
			{1,1,-5},
			{0,1,-6},
			{1,1,-6}
		},
		{//back1
			{0,1,-5},
			{0,0,-5},
			{0,0,-6},
		},
		{//back2
			{0,1,-5},
			{0,0,-6},
			{0,1,-6}
		},
		{//top1
			{1,0,-6},
			{1,1,-6},
			{0,1,-6},
		},
		{//top2
			{1,0,-6},
			{0,1,-6},
			{0,0,-6}
		},
		{//bottom1
			{1,0,-5},
			{1,1,-5},
			{0,1,-5},
		},
		{//bottom2
			{1,0,-5},
			{0,1,-5},
			{0,0,-5}
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

	float rotationAngle = 0.05f;
	 // ********************
};