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
			if (self)
			{
				self->width_ = width;
				self->height_ = height;
				glViewport(0, 0, width, height);
				if (self->fontView_)
					self->fontView_->onResize(width, height);
				if (self->sorterView_)
					self->sorterView_->onResize(width, height);
			}
		});

	// font model/view
	fontModel_ = std::make_unique<FontModel>("arial.ttf", 0, 75);
	fontView_ = std::make_unique<FontView>(*fontModel_, width_, height_);
	fontView_->upload();

	// sorter model/view
	const unsigned int numberOfLines = 500;
	sorterModel_ = std::make_unique<SorterModel>(numberOfLines, width_, height_);
	sorterView_ = std::make_unique<SorterView>(*sorterModel_, width_, height_);
	sorterView_->upload();

	sorterModel_->setSortingAlgorithm(std::make_unique<InsertionSort>());
} // end of constructor

AppController::~AppController()
{
	// destroy window if still active
	if (window_) glfwDestroyWindow(window_);
	glfwTerminate();
} // end of destructor

void AppController::run()
{
	unsigned int steps = 100;
	while (!glfwWindowShouldClose(window_))
	{
		// set color to display after clear (state-setting function)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// clear the screen colors (state-using function)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// process and handle input from user
		processInput();

		// check for sorting done
		if (sorterModel_->step(steps))
		{
			currTime = currTime;
			fontView_->render("DONE!", 0.0f, height_ / 2.0f - 75.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}
		else
		{
			currTime = glfwGetTime();
		}

		// sorter render
		sorterView_->render();

		// font render
		fontView_->render("Time: " + std::to_string(currTime), 0.0f, height_ / 2.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		fontView_->render(algoText_, width_ / 2.0f, height_ - 100.0f, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

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
	
	// press '1' key
	if (glfwGetKey(window_, GLFW_KEY_1) == GLFW_PRESS)
	{
		glfwSetTime(0.0);
		std::cout << "BUBBLE SORT\n";
		sorterModel_->setSortingAlgorithm(std::make_unique<BubbleSort>());
		algoText_ = "BUBBLE SORT";
	}
	// press '2' key
	if (glfwGetKey(window_, GLFW_KEY_2) == GLFW_PRESS)
	{
		glfwSetTime(0.0);
		std::cout << "INSERTION SORT\n";
		sorterModel_->setSortingAlgorithm(std::make_unique<InsertionSort>());
		algoText_ = "INSERTION SORT";
	}
	// press '3' key
	if (glfwGetKey(window_, GLFW_KEY_3) == GLFW_PRESS)
	{
		std::cout << "#3\n";
	}
	if (glfwGetKey(window_, GLFW_KEY_4) == GLFW_PRESS)
	{
		std::cout << "#4\n";
	}
	if (glfwGetKey(window_, GLFW_KEY_5) == GLFW_PRESS)
	{
		std::cout << "#5\n";
	}
} // end of processInput()