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
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
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

Vertex vertex[8];
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_CULL_FACE);
	glTranslatef(0.f, 0.f, -5.f);

	glewInit();

	gpp::MyVector3f vertices[] = { {-1,1,1 }, {-1,-1,1} , {1,1,1} , {1,-1,1} , {-1,-1,-1} , {-1,1,-1} , {1,1,-1} , {1,-1,-1} };
	for (int i = 0; i < 8; i++)
	{
		trianglePoints[i] = vertices[i];
	}
	int vertex_index[] = { 1,3,0 , 3,2,0 , 5,4,0 , 4,1,0 , 7,6,3 , 6,2,3 , 6,5,2 , 5,0,2 , 5,6,4 , 6,7,4 , 4,7,1 , 1,7,3 };
	int colors[] = { .25,.75,.5, 0,1,0 , 0.1,.2,.3 , 1,0,0 , 0,1,0 ,1,0,1 , .33,.66,.99 , .69,.420,.1000101 };

	/* Vertices counter-clockwise winding */

	for (int i = 0,j=0; i < 8; i++, j+=3)
	{
		vertex[i].coordinate[0] = trianglePoints[i].getX();
		vertex[i].coordinate[1] = trianglePoints[i].getY();
		vertex[i].coordinate[2] = trianglePoints[i].getZ();

		vertex[i].color[0] = colors[j];
		vertex[i].color[1] = colors[j+1];
		vertex[i].color[2] = colors[j+2];
	}

	for (int i = 0; i < 36; i++)
	{
		triangles[i] = vertex_index[i];
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();
	}

	// update the centre point of the cube
	gpp::MyVector3f centre;
	//calculate the centre point of the circle
	for (int i = 0,j=0; i < 24; i += 3,j++)
	{
		centre.setX(centre.getX() + trianglePoints[j].getX());
		centre.setY(centre.getY() + trianglePoints[j].getY());
		centre.setZ(centre.getZ() + trianglePoints[j].getZ());
	}

	centre.setX(centre.getX() / 8.f);
	centre.setY(centre.getY() / 8.f);
	centre.setZ(centre.getZ() / 8.f);

	if (Keyboard::isKeyPressed(Keyboard::Q))
	{// rotate Z
		for (auto& v : trianglePoints)
		{
			// rotate the points
			v -= centre;
			v = gpp::Matrix3f::rotateZ(0.4) * v;

			// translate them back to where they were
			v += centre;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{ // rotate X
		for (auto& v : trianglePoints)
		{
			v -= centre;

			v = gpp::Matrix3f::rotateX(0.4) * v;

			v += centre;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::E))
	{// rotatae Y 
		for (auto& v : trianglePoints)
		{
			v -= centre;

			v = gpp::Matrix3f::rotateY(0.4) * v;

			v += centre;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::Z))
	{ // scale down 
		for (auto& v : trianglePoints)
		{
			v = gpp::Matrix3f::scale(0.99) * v;
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::X))
	{ // scale up
		for (auto& v : trianglePoints)
		{
			v = gpp::Matrix3f::scale(1.01) * v;
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{ // move left
		for (auto& v : trianglePoints)
		{
			float z = v.getZ();
			v.setZ(1);
			v = gpp::Matrix3f::translate(gpp::MyVector3f{ -0.01,0,0 }) * v;
			v.setZ(z);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{ // move right 
		for (auto& v : trianglePoints)
		{
			float z = v.getZ();
			v.setZ(1);
			v = gpp::Matrix3f::translate(gpp::MyVector3f{ 0.01,0,0 }) * v;
			v.setZ(z);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::F))
	{ // move up
		for (auto& v : trianglePoints)
		{
			float z = v.getZ();
			v.setZ(1);
			v = gpp::Matrix3f::translate(gpp::MyVector3f{ 0,0.01,0 }) * v;
			v.setZ(z);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{ // move down 
		for (auto& v : trianglePoints)
		{
			float z = v.getZ();
			v.setZ(1);
			v = gpp::Matrix3f::translate(gpp::MyVector3f{ 0,-0.01,0 }) * v;
			v.setZ(z);
		}
	}


	// update array
	for (int i = 0; i < 8; i++)
	{
		vertex[i].coordinate[0] = trianglePoints[i].getX();
		vertex[i].coordinate[1] = trianglePoints[i].getY();
		vertex[i].coordinate[2] = trianglePoints[i].getZ();
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 8, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

