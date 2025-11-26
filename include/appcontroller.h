#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "fontmodel.h"
#include "fontview.h"
#include "sortermodel.h"
#include "bubblesort.h"
#include "insertionsort.h"
#include "selectionsort.h"
#include "quicksort.h"
#include "sorterview.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>


class AppController
{
public:
	AppController(int width, int height, const char* windowTitle);
	~AppController();

	void run();

private:
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

	// the font
	std::unique_ptr<FontModel> fontModel_;
	std::unique_ptr<FontView> fontView_;

	// the sorter
	std::unique_ptr<SorterModel> sorterModel_;
	std::unique_ptr<SorterView> sorterView_;

	// current time tracker
	double currTime = 0.0;
	// default algorithm text
	std::string algoText_ = "BUBBLE SORT";
};

#endif
