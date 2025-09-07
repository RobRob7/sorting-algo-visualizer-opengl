#include "fontview.h"

//--- PUBLIC ---//
FontView::FontView(const FontModel& fontModel, int windowWidth, int windowHeight)
	: fontModel_(fontModel), windowWidth_(windowWidth), windowHeight_(windowHeight), vao_(0), vbo_(0)
{
	// create font shader
	fontShader_ = std::make_unique<Shader>("/font/shader.vert", "/font/shader.frag");
	// enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
} // end of constructor

FontView::~FontView()
{
	// delete textures
	for (const auto& pair : characters_)
	{
		glDeleteTextures(1, &pair.second.textureID);
	} // end for
	// delete VAO, VBO
	if (vao_) glDeleteVertexArrays(1, &vao_);
	if (vbo_) glDeleteBuffers(1, &vbo_);
} // end of destructor

void FontView::upload()
{
	// no byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (const auto& pair : fontModel_.getCharacters())
	{
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			pair.second.size[0],
			pair.second.size[1],
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			pair.second.bitmap.data()
		);

		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// now store character for later use
		CharacterGL character = {
			texture,
			glm::ivec2{pair.second.size[0], pair.second.size[1]},
			glm::ivec2{pair.second.bearing[0], pair.second.bearing[1]},
			pair.second.advance
		};
		characters_.insert(std::pair<char, CharacterGL>(pair.first, character));
	} // end for

	// VAO, VBO setup
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	glBindVertexArray(vao_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
} // end of upload()

void FontView::render(const std::string& text, float x, float y, float scale, glm::vec3 color)
{
	// use font shader, set uniforms
	fontShader_->use();
	fontShader_->setVec3("textColor", color);
	glm::mat4 projection = glm::ortho(
		0.0f, static_cast<float>(windowWidth_),
		0.0f, static_cast<float>(windowHeight_)
	);
	fontShader_->setMat4("projection", projection);
	fontShader_->setInt("text", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao_);

	// loop through each character of text to render
	for (char c : text)
	{
		const CharacterGL& ch = characters_.at(c);

		float xpos = x + ch.bearing.x * scale;
		float ypos = y - (ch.size.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;

		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vbo_);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// advance cursors for next glyph (advance is 1/64 pixels)
		x += (ch.advance >> 6) * scale;
	} // end for

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
} // end of renderText()


void FontView::onResize(int width, int height)
{
	// set new window sizes
	windowWidth_ = width;
	windowHeight_ = height;
} // end of onResize()