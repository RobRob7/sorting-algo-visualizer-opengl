#include "glview.h"

//--- PUBLIC ---//
GLView::GLView(int width, int height)
	: width_(width), height_(height),
	shader_(Shader("../../../res/shader/shader.vert", "../../../res/shader/shader.frag"))
{
	createBuffers();
	glViewport(0, 0, width_, height_);
} // end of constructor

GLView::~GLView()
{
	if (vao_) glDeleteVertexArrays(1, &vao_);
	if (vbo_) glDeleteBuffers(1, &vbo_);
} // end of destructor

void GLView::onResize(int width, int height)
{
	width_  = width;
	height_ = height;
	glViewport(0, 0, width_, height_);
} // end of onResize()

void GLView::upload(const TriangleModel& model)
{
	// temp
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	const auto& verts = model.vertices();
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verts.size(), verts.data(), GL_STATIC_DRAW);

	// Positions (location=0): 2 floats, stride 5 floats
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Colors (location=1): 3 floats, stride 5 floats, offset 2 floats
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
} // end of upload()

void GLView::render()
{
	// set color to display after clear (state-setting function)
	glClearColor(clearR_, clearG_, clearB_, 1.0f);
	// clear the screen colors (state-using function)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// temp
	shader_.use();
	glBindVertexArray(vao_);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
} // end of render()

void GLView::setClearColor(float r, float g, float b)
{
	clearR_ = r;
	clearG_ = g;
	clearB_ = b;
} // end of setClearColor()

//--- PRIVATE ---//
void GLView::createBuffers()
{
	// temp
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
} // end of createBuffers()