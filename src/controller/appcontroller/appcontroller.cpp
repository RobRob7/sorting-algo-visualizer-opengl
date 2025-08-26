#include "appcontroller.h"

//--- PUBLIC ---//
AppController::AppController(int width, int height, const char* windowTitle)
	: width_(width), height_(height), windowTitle_(windowTitle)
{
	// intialize GLFW
	if (!glfwInit())
	{
		throw std::runtime_error("GLFW initialization error!");
	}

	// specify major OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// specify minor OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// specify OpenGL core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// apple device dependent
	#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif

	// WINDOW CREATION + CHECK
	window_ = glfwCreateWindow(width_, height_, windowTitle_, NULL, NULL);
	if (!window_)
	{
		glfwTerminate();
		throw std::runtime_error("GLFW window creation failure!");
	} // end if

	// tell GLFW to make the context of our window the main context on the current thread
	glfwMakeContextCurrent(window_);

	// vsync
	glfwSwapInterval(1);

	// INITIALIZE GLAD + CHECK
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		glfwDestroyWindow(window_);
		glfwTerminate();
		throw std::runtime_error("GLAD initialization failure!");
	} // end if

	// set user pointer for callbacks
	glfwSetWindowUserPointer(window_, this);
	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height)
		{
			auto* self = static_cast<AppController*>(glfwGetWindowUserPointer(window));
			if (self && self->view_) self->view_->onResize(width, height);
		});

	view_ = std::make_unique<GLView>(width_, height_);
	model_ = std::make_unique<TriangleModel>();
	view_->upload(*model_);
} // end of constructor

AppController::~AppController()
{
	// destroy window if still active
	if (window_) glfwDestroyWindow(window_);
	glfwTerminate();
} // end of destructor

void AppController::run()
{
	while (!glfwWindowShouldClose(window_))
	{
		processInput();
		view_->render();
		glfwSwapBuffers(window_);
		glfwPollEvents();
	} // end while
} // end of run()

//--- PRIVATE ---//
void AppController::processInput()
{
	// press 'esc' key to close window
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window_, true);
	}
} // end of processInput()