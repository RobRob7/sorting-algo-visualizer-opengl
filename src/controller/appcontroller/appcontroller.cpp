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
	window_ = glfwCreateWindow(width_, height_, windowTitle_, nullptr, nullptr);
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
		throw std::runtime_error("GLAD initialization failure!");
	} // end if

	// set user pointer for callbacks
	glfwSetWindowUserPointer(window_, this);
	glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height)
		{
			auto* self = static_cast<AppController*>(glfwGetWindowUserPointer(window));
			if (self && self->view_) self->view_->onResize(width, height);
		});

	//// enable for text rendering
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// triangle model/view
	//model_ = std::make_unique<TriangleModel>();
	//view_  = std::make_unique<GLView>(width_, height_);
	//view_->upload(*model_);

	// font model/view
	fontModel_ = std::make_unique<FontModel>("arial.ttf", 0, 50);
	Shader fontShader("/font/shader.vert", "/font/shader.vert");
	fontView_ = std::make_unique<FontView>(*fontModel_, fontShader);
	fontView_->upload();
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
		glm::mat4 projection = glm::ortho(
			0.0f, static_cast<float>(width_),
			0.0f, static_cast<float>(height_)
		);

		processInput();
		// triangle render
		view_->render();

		// font render
		fontView_->drawText("TESTING TEXT TEST", 25.0f, 25.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		fontView_->render(projection, glm::mat4(1.0f));

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