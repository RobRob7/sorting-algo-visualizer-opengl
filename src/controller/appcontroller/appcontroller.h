#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "../../view/glview/glview.h"
#include "../../model/trianglemodel/trianglemodel.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>


class AppController
{
public:
	// constructor
	AppController(int width, int height, const char* windowTitle);
	// destructor
	~AppController();

	// this function runs the application render loop
	void run();

private:
	// this function processes and handles input from user
	void processInput();
private:
	// width of window
	int width_;
	// height of window
	int height_;
	// window title name
	const char* windowTitle_;
	// GLFWwindow instance
	GLFWwindow* window_ = nullptr;

	// the view (VAO/VBO setup + shader)
	std::unique_ptr<GLView> view_;
	// the model (vertex data)
	std::unique_ptr<TriangleModel> model_;
};

#endif
