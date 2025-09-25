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
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	// specify minor OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// specify OpenGL core-profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
				if (self->sorterModel_)
					self->sorterModel_->updateForResize(width, height);
				if (self->sorterView_)
					self->sorterView_->onResize(width, height);
			}
		});

	// font model/view
	const unsigned int fontSize = 75;
	fontModel_ = std::make_unique<FontModel>("arial.ttf", 0, fontSize);
	fontView_ = std::make_unique<FontView>(*fontModel_, width_, height_);
	fontView_->upload();

	// sorter model/view
	const unsigned int numberOfLines = 1000;
	sorterModel_ = std::make_unique<SorterModel>(numberOfLines, width_, height_);
	sorterView_ = std::make_unique<SorterView>(*sorterModel_, width_, height_);
	sorterView_->upload();

	// set bubble sort as initial algorithm
	sorterModel_->setSortingAlgorithm(std::make_unique<BubbleSort>());
} // end of constructor

AppController::~AppController()
{
	// destroy window if still active
	if (window_) glfwDestroyWindow(window_);
	glfwTerminate();
} // end of destructor

void AppController::run()
{
	// number of steps per frame for animation
	unsigned int steps = 50;
	// color of time font
	glm::vec3 timeFontColor{ 1.0f, 0.0f, 0.0f };
	// algo title font color
	glm::vec3 algoFontColor{ 0.0f, 0.0f, 1.0f };
	// tip font color
	glm::vec3 tipFontColor{ 1.0f, 1.0f, 1.0f };
	while (!glfwWindowShouldClose(window_))
	{
		// set color to display after clear (state-setting function)
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// clear the screen colors (state-using function)
		glClear(GL_COLOR_BUFFER_BIT);

		// process and handle input from user
		processInput();

		// render selection tips
		fontView_->render("Select Algorithm Using Key (ESC to end):", 0.0f, height_ - 100.0f, 1.0f, tipFontColor);
		fontView_->render("1 - Bubble Sort", 0.0f, height_ - 175.0f, 1.0f, tipFontColor);
		fontView_->render("2 - Insertion Sort", 0.0f, height_ - 250.0f, 1.0f, tipFontColor);
		fontView_->render("3 - Selection Sort", 0.0f, height_ - 325.0f, 1.0f, tipFontColor);
		fontView_->render("4 - Quick Sort", 0.0f, height_ - 400.0f, 1.0f, tipFontColor);

		// check for sorting done
		if (sorterModel_->step(steps))
		{
			fontView_->render("DONE!", 0.0f, height_ / 2.0f - 75.0f, 1.0f, timeFontColor);
		}
		else
		{
			currTime = glfwGetTime();
		}

		// sorter render
		sorterView_->render();

		// font render (time counter and algo selected)
		fontView_->render("Time: " + std::to_string(currTime), 0.0f, height_ / 2.0f, 1.0f, timeFontColor);
		fontView_->render(algoText_ + " (N=" + std::to_string(sorterModel_->getLinePositions().size()) + ")", width_ / 2.0f, height_ - 100.0f, 1.0f, algoFontColor);

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
		glfwSetTime(0.0);
		std::cout << "SELECTION SORT\n";
		sorterModel_->setSortingAlgorithm(std::make_unique<SelectionSort>());
		algoText_ = "SELECTION SORT";
	}
	// press '4' key
	if (glfwGetKey(window_, GLFW_KEY_4) == GLFW_PRESS)
	{
		glfwSetTime(0.0);
		std::cout << "QUICK SORT\n";
		sorterModel_->setSortingAlgorithm(std::make_unique<QuickSort>());
		algoText_ = "QUICK SORT";
	}
} // end of processInput()