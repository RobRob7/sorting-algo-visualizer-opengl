#ifndef SORTERVIEW_H
#define SORTERVIEW_H

#include "../model/sortermodel/sortermodel.h"
#include "../shader/shader.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>

class SorterView
{
public:
	SorterView(const SorterModel& sorterModel, int windowWidth, int windowHeight);
	~SorterView();

	// upload vao, vbo
	void upload();
	// render the lines
	void render();
	// update new window width, height
	void onResize(int width, int height);

private:
	// window width, height
	unsigned int windowWidth_;
	unsigned int windowHeight_;
	// sorter model
	const SorterModel& sorterModel_;
	// sorter model vertices
	const std::vector<float>& sorterVertices_ = sorterModel_.getVertices();
	// sorter model line positions
	const std::vector<float>& sorterLinePositions_ = sorterModel_.getLinePositions();
	// sorter model line scale
	const std::vector<float>& sorterLineScale_ = sorterModel_.getLineScale();
	// sorter line shader
	std::unique_ptr<Shader> sorterShader_;
	// sorter VAO
	unsigned int vao_;
	// sorter VBO
	unsigned int vbo_;
};

#endif
