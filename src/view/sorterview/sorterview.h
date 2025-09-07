#ifndef SORTERVIEW_H
#define SORTERVIEW_H

#include "../iview/iview.h"
#include "../model/sortermodel/sortermodel.h"
#include "../shader/shader.h"

#include <glad/glad.h>
#include <vector>

class SorterView : public IView
{
public:
	SorterView(const SorterModel& sorterModel, int windowWidth, int windowHeight);
	~SorterView();

	void upload() override;
	void onResize(int width, int height);

private:
	// window width, height
	unsigned int windowWidth_;
	unsigned int windowHeight_;
	// sorter model
	const SorterModel& sorterModel_;
	// sorter line shader
	std::unique_ptr<Shader> sorterShader_;
	// sorter VAO
	unsigned int vao_;
	// sorter VBO
	unsigned int vbo_;
};

#endif
