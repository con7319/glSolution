
#include "core.h"
#include "math.h"


// global variables

// Window size
const unsigned int initWidth = 512;
const unsigned int initHeight = 512;
int number = 1;
float M_PI = 3.14159265358979323846f;

// Function prototypes
void renderScene();
void resizeWindow(GLFWwindow* window, int width, int height);
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void DrawPolygon(int _x, int _y, int _sides, float _radius);
void updateScene();


int main() {

	//
	// 1. Initialisation
	//
	

	// Initialise glfw and setup window
	glfwInit();

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_COMPAT_PROFILE, GLFW_TRUE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);

	GLFWwindow* window = glfwCreateWindow(initWidth, initHeight, "Wow , shapes...", NULL, NULL);

	// Check window was created successfully
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window!\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	

	// Set callback functions to handle different events
	glfwSetFramebufferSizeCallback(window, resizeWindow); // resize window callback
	glfwSetKeyCallback(window, keyboardHandler); // Keyboard input callback


	// Initialise glew
	glewInit();

	
	// Setup window's initial size
	resizeWindow(window, initWidth, initHeight);

	// Initialise scene - geometry and shaders etc
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // setup background colour to be black
    //gluOrtho2D(-3, 3, -3, 3); // changes screen dimensions from -1 and 1


	//
	// 2. Main loop
	// 
	

	// Loop while program is not terminated.
	while (!glfwWindowShouldClose(window)) {

		updateScene();
		renderScene();						// Render into the current buffer
		glfwSwapBuffers(window);			// Displays what was just rendered (using double buffering).

		// Poll events (key presses, mouse events)
		// glfwWaitEvents();				// Use this if no animation.
		// glfwWaitEventsTimeout(1.0/60.0);	// Use this to animate at 60 frames/sec (timing is NOT reliable)
		glfwPollEvents();					// Use this version when animating as fast as possible
	}

	glfwTerminate();
	return 0;
}



// renderScene - function to render the current scene
void renderScene()
{
	// Clear the rendering window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	// Render objects here...
    switch (number) {
    case 0: // Triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        break;

    case 1: // Larger Triangle
        glBegin(GL_TRIANGLES);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
        glEnd();
        break;

    case 2: // Square
        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();
        break;

    case 3: // Circle
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.0f); // Center of the circle
        for (int i = 0; i <= 360; i += 10) {
            float angle = i * M_PI / 180.0f; // Convert degrees to radians
            glVertex2f(cos(angle) * 0.5f, sin(angle) * 0.5f);
        }
        glEnd();
        break;

    case 4: // Star 
        glBegin(GL_LINE_LOOP);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.2f, 0.1f);
        glVertex2f(-0.5f, 0.1f);
        glVertex2f(-0.25f, -0.2f);
        glVertex2f(-0.4f, -0.5f);
        glVertex2f(0.0f, -0.3f);
        glVertex2f(0.4f, -0.5f);
        glVertex2f(0.25f, -0.2f);
        glVertex2f(0.5f, 0.1f);
        glVertex2f(0.2f, 0.1f);
        glEnd();
        break;

    case 5: // Hexagon
        glBegin(GL_POLYGON);
        for (int i = 0; i < 6; i++) {
            float angle = i * 60 * M_PI / 180.0f; // Convert degrees to radians
            glVertex2f(cos(angle) * 0.5f, sin(angle) * 0.5f);
        }
        glEnd();
        break;

    case 6: // Spiral 
        glBegin(GL_LINE_STRIP);
        for (float t = 0; t <= 2 * M_PI * 3; t += 0.1f) { // 3 loops
            float radius = t / (2 * M_PI * 3); // Gradually increase radius
            glVertex2f(cos(t) * radius, sin(t) * radius);
        }
        glEnd();
        break;

    case 7: // Heart (non-traditional)
        glBegin(GL_LINE_STRIP);
        for (float t = 0; t <= 2 * M_PI; t += 0.01f) {
            float x = 0.5f * 16 * pow(sin(t), 3);
            float y = 0.5f * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
            glVertex2f(x / 15.0f, y / 15.0f);
        }
        glEnd();
        break;

    case 8: // Random Polygon (non-traditional)
        glBegin(GL_POLYGON);
        for (int i = 0; i < 8; i++) { // 8-sided polygon
            float angle = i * 45 * M_PI / 180.0f; // Convert degrees to radians
            float radius = 0.3f + (float)rand() / RAND_MAX * 0.2f; // Random radius
            glVertex2f(cos(angle) * radius, sin(angle) * radius);
        }
        glEnd();
        break;
    }


	

}


// Function to call when window resized
void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);		// Draw into entire window
}
void DrawPolygon(int _x, int _y, int _sides, float _radius)
{
	//while (int i != _sides; )
}

// Function to call to handle keyboard input
void keyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) {

		// check which key was pressed...
		switch (key)
		{
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, true);
				break;

			case GLFW_KEY_SPACE:
				number = (number +1) % 9;
				glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				break;

			default:
			{
			}
		}
	}
	else if (action == GLFW_RELEASE) {
		// handle key release events
	}
}


// Function called to animate elements in the scene
void updateScene() {


}

