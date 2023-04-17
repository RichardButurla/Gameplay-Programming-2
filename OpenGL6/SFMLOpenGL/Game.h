#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <Vector3.h>
#include <MyVector3.h>
#include <Matrix.h>

using namespace std;
using namespace gpp;



class myVector3
{
public:
	myVector3(float t_x, float t_y, float t_z) : x(t_x), y(t_y), z(t_z)
	{}

	float x;
	float y;
	float z;
};

static const int MAX_TRIANGLE_POINTS = 3;
static const int MAX_CUBE_POINTS = 8;
static const int MAX_TRIANGLES = 12;
static const int MAX_CUBE_FACES = 6;


class Game
{
public:
	Game();
	~Game();
	void run();
private:
	sf::Window window;
	bool isRunning = false;
	void initialize();
	void update();
    void processEvents(sf::Event event);
	void render();
	void unload();

    sf::Clock clock;
    sf::Time elapsed;

	float rotationAngle = 0.0f;

    myVector3 vertexes[24]
	{
        // Front face
        { -0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f,  0.5f },
        {  0.5f,  0.5f,  0.5f },
        { -0.5f,  0.5f,  0.5f },
        // Right face
        {  0.5f, -0.5f,  0.5f },
        {  0.5f, -0.5f, -0.5f },
        {  0.5f,  0.5f, -0.5f },
        {  0.5f,  0.5f,  0.5f },
        // Back face
        {  0.5f, -0.5f, -0.5f },
        { -0.5f, -0.5f, -0.5f },
        { -0.5f,  0.5f, -0.5f },
        {  0.5f,  0.5f, -0.5f },
        // Left face
        { -0.5f, -0.5f, -0.5f },
        { -0.5f, -0.5f,  0.5f },
        { -0.5f,  0.5f,  0.5f },
        { -0.5f,  0.5f, -0.5f },
        // Top face
        { -0.5f,  0.5f,  0.5f },
        {  0.5f,  0.5f,  0.5f },
        {  0.5f,  0.5f, -0.5f },
        { -0.5f,  0.5f, -0.5f },
        // Bottom face
        { -0.5f, -0.5f, -0.5f },
        {  0.5f, -0.5f, -0.5f },
        {  0.5f, -0.5f,  0.5f },
        { -0.5f, -0.5f,  0.5f }
	};

	myVector3 m_cubeColors[MAX_CUBE_FACES]
	{
		{1.0f, 0.0f, 0.0f},//V0(red)
		{0.0f, 1.0f, 0.0f}, //V1(green)
		{0.0f, 0.0f, 1.0f}, //V2(blue)
		{1.0f, 1.0f, 0.0f}, //V2(blue)
		{1.0f, 0.0f, 1.0f}, //V2(magenta)
		{0.0f, 1.0f, 1.0f}, //V2(cyan)
	};
};