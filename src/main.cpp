#include "controller/appcontroller/appcontroller.h"

// window settings
unsigned int width = 800;
unsigned int height = 600;
const char* windowName = "Sorting Visualizer OpenGL";

// main driver
int main()
{
	try
	{
		AppController app(width, height, windowName);
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Fatal error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
} // end of main