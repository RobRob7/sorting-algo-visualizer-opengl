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

	glBufferData(GL_ARRAY_BUFFER, sorterVertices_.size() * sizeof(float), sorterVertices_.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
} // end of upload()

void SorterView::render()
{
	// pvm calculation
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth_), 0.0f, static_cast<float>(windowHeight_));
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 model = glm::mat4(1.0f);
	
	glm::mat4 pv = projection * view;
	glm::mat4 pvm = pv * model;

	// use sorter shader
	sorterShader_->use();
	
	// render lines
	glBindVertexArray(vao_);
	for (size_t i = 0; i < sorterLinePositions_.size(); ++i)
	{
		glm::mat4 linesModel = glm::mat4(1.0f);
		linesModel = glm::translate(linesModel, glm::vec3(sorterLinePositions_[i], 0.0f, 0.0f));
		linesModel = glm::scale(linesModel, glm::vec3(1.0f, sorterLineScale_[i], 1.0f));
		glm::mat4 linePVM = pv * linesModel;
		sorterShader_->setMat4("pvm", linePVM);
		glDrawArrays(GL_LINES, 0, 2);
	} // end for

	glBindVertexArray(0);
} // end of render()

void SorterView::onResize(int width, int height)
{
	// set new window sizes
	windowWidth_ = width;
	windowHeight_ = height;

	// tell model to recompute sizes
	const_cast<SorterModel&>(sorterModel_).updateForResize(width, height);
} // end of onResize()