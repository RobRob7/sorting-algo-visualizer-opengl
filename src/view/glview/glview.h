#ifndef GLVIEW_H
#define GLVIEW_H

#include "../shader/shader.h"
#include "../model/trianglemodel/trianglemodel.h"

#include <glad/glad.h>

class GLView
{
public:
	GLView(int width, int height);
	~GLView();

	void onResize(int width, int height);
	void upload(const TriangleModel& model);
	void render();
	void setClearColor(float r, float g, float b);

private:
	void createBuffers();

private:
	int width_;
	int height_;
	float clearR_ = 0.1f;
	float clearG_ = 0.1f;
	float clearB_ = 0.1f;

	unsigned int vao_ = 0;
	unsigned int vbo_ = 0;

	Shader shader_;
};

#endif
