#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "../../model/fontmodel/fontmodel.h"
#include "../../view/fontview/fontview.h"
#include "../../model/sortermodel/sortermodel.h"
#include "../../model/sortermodel/sortingalgo/bubblesort.h"
#include "../../model/sortermodel/sortingalgo/insertionsort.h"
#include "../../model/sortermodel/sortingalgo/selectionsort.h"
#include "../../view/sorterview/sorterview.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <stdexcept>


class AppController
{
public:
	AppController(int width, int height, const char* windowTitle);
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

	// the font model
	std::unique_ptr<FontModel> fontModel_;
	// the font view
	std::unique_ptr<FontView> fontView_;

	// the sorter model
	std::unique_ptr<SorterModel> sorterModel_;
	// the sorter view
	std::unique_ptr<SorterView> sorterView_;

	// current time tracker
	double currTime = 0.0;
	// default algorithm text
	std::string algoText_ = "BUBBLE SORT";
};

#endif
