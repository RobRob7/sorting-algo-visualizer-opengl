#ifndef FONTVIEW_H
#define FONTVIEW_H

#include "../iview/iview.h"
#include "../model/fontmodel/fontmodel.h"
#include "../shader/shader.h"

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
	FontView(const FontModel& fontModel, Shader& fontShader);
	~FontView();

	void upload() override;
	void render(const glm::mat4& projection, const glm::mat4& view) override;
	void drawText(const std::string& text, float x, float y, float scale, glm::vec3 color);

private:
	// font model
	const FontModel& fontModel_;
	// font shader program
	Shader& fontShader_;
	// map of characters to render
	std::map<char, CharacterGL> characters_;
	// font VAO
	unsigned int vao_;
	// font VBO
	unsigned int vbo_;
	
	struct PendingText
	{
		std::string text;
		float x, y, scale;
		glm::vec3 color;
	};
	std::vector<PendingText> textQueue_;
};

#endif
