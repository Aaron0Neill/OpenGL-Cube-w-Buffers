#include <iostream>
#include <GL/glew.h>
#include <GL/wglew.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <array>

#include "MyVector3f.h"
#include "Matrix3f.h"


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
	void render();
	void unload();

	Clock clock;
	Time elapsed;

	array<gpp::MyVector3f, 8> trianglePoints;
	float rotationAngle = 0.0f;
};