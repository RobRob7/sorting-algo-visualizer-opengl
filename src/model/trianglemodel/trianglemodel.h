#ifndef TRIANGLEMODEL_H
#define TRIANGLEMODEL_H

#include <vector>

class TriangleModel
{
public:
	// this function returns vertices (+color)
	const std::vector<float>& vertices() const;

private:
	// vertices + color data of triangle
	const std::vector<float> vertices_ =
	{
		//	x      y        r     g     b
			0.0f,  0.5f,    1.0f, 0.0f, 0.0f, // top (red)
		   -0.5f, -0.5f,    0.0f, 1.0f, 0.0f, // left (green)
			0.5f, -0.5f,    0.0f, 0.0f, 1.0f  // right (blue)
	};
};

#endif


