#ifndef FONTVIEW_H
#define FONTVIEW_H

#include "../iview/iview.h"
#include "../model/fontmodel/fontmodel.h"
#include "../shader/shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

struct CharacterGL
{
	// ID of character texture
	unsigned int textureID;
	// size of glyph
	glm::ivec2 size;
	// offset from baseline to left/top of glyph
	glm::ivec2 bearing;
	// offset to advance to next glyph
	unsigned int advance;
};

class FontView : public IView
{
public:
	FontView(const FontModel& fontModel, int windowWidth, int windowHeight);
	~FontView();

	void upload() override;
	void render(const std::string& text, float x, float y, float scale, glm::vec3 color);
	void onResize(int width, int height);

private:
	// window width, height
	unsigned int windowWidth_;
	unsigned int windowHeight_;
	// font model
	const FontModel& fontModel_;
	// font shader
	std::unique_ptr<Shader> fontShader_;
	// map of characters to render
	std::map<char, CharacterGL> characters_;
	// font VAO
	unsigned int vao_;
	// font VBO
	unsigned int vbo_;
};

#endif
