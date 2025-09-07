#include "sorterview.h"

//--- PUBLIC ---//
SorterView::SorterView(const SorterModel& sorterModel, int windowWidth, int windowHeight)
	: sorterModel_(sorterModel), windowWidth_(windowWidth), windowHeight_(windowHeight), vao_(0), vbo_(0)
{
	// create sorter shader
	sorterShader_ = std::make_unique<Shader>("/sorter/shader.vert", "/sorter/shader.frag");
} // end of constructor

SorterView::~SorterView()
{
	// delete VAO, VBO
	if (vao_) glDeleteVertexArrays(1, &vao_);
	if (vbo_) glDeleteBuffers(1, &vbo_);
} // end of destructor

void SorterView::upload()
{
	// VAO, VBO setup
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	glBufferData(GL_ARRAY_BUFFER, sorterModel_.getVertices().size() * sizeof(float), sorterModel_.getVertices().data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
} // end of upload()

void SorterView::onResize(int width, int height)
{
	windowWidth_ = width;
	windowHeight_ = height;
	glViewport(0, 0, windowWidth_, windowHeight_);
} // end of onResize()