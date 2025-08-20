#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "shader/shader.h"

// is called each time window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// is called when certain input action observed
void processInput(GLFWwindow* window);

// window size settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// main driver code
int main() {
	// intialize GLFW
	glfwInit();
	// specify major OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// specify minor OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// specify OpenGL core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// WINDOW CREATION + CHECK
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Sorting Algorithms", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "GLFW window creation failure!" << std::endl;
		glfwTerminate();
		return -1;
	} // end if

	// tell GLFW to make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window);

	// callback functions
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// INITIALIZE GLAD + CHECK
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD initialization failure!" << std::endl;
		return -1;
	} // end if

	// enable depth test
	glEnable(GL_DEPTH_TEST);

	// shader creation
	//Shader myShader("resources/shaders/10/vs.glsl", "resources/shaders/10/fs.glsl");

	// cube vertices
	std::vector<float> vertices = {
		// positions									// colors
		0.0f, 0.0f, 0.0f,								0.0f, 0.75f, 0.75f,
		0.0f, static_cast<float>(SCR_HEIGHT), 0.0f,		0.75f, 0.0f, 0.75f
	};

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// process any inputs
		processInput(window);

		// RENDER //
		// set color to display after clear (state-setting function)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// clear the screen colors (state-using function)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	} // end while

	// clean/delete all GLFW's resources that were allocated
	glfwTerminate();
	return 0;
} // end main


// this function is called whenever window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);

} // end of framebuffer_size_callback(...)

// this function is called whenever an input is observed
void processInput(GLFWwindow* window) {
	// window exit
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
} // end of processInput(...)

