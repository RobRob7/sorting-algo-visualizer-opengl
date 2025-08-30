#include "fontview.h"

//--- PUBLIC ---//
FontView::FontView(const FontModel& fontModel, Shader& fontShader)
	: fontModel_(fontModel), fontShader_(fontShader), vao_(0), vbo_(0)
{
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
			glm::ivec2(pair.second.size[0], pair.second.size[1]),
			glm::ivec2(pair.second.bearing[0], pair.second.bearing[1]),
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
} // end of Load()

void FontView::render(const glm::mat4& projection, const glm::mat4& view)
{
	fontShader_.use();
	fontShader_.setMat4("projection", projection);
	//fontShader_.setMat4("view", view);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vao_);

	for (const auto& pending : textQueue_)
	{
		fontShader_.setVec3("textColor", pending.color);

		float x = pending.x;
		float y = pending.y;

		for (char c : pending.text)
		{
			const CharacterGL& ch = characters_.at(c);

			float xpos = x + ch.bearing.x * pending.scale;
			float ypos = y - (ch.size.y - ch.bearing.y) * pending.scale;
			float w = ch.size.x * pending.scale;
			float h = ch.size.y * pending.scale;

			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos,     ypos,       0.0f, 1.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },

				{ xpos,     ypos + h,   0.0f, 0.0f },
				{ xpos + w, ypos,       1.0f, 1.0f },
				{ xpos + w, ypos + h,   1.0f, 0.0f }
			};

			glBindTexture(GL_TEXTURE_2D, ch.textureID);
			glBindBuffer(GL_ARRAY_BUFFER, vbo_);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			x += (ch.advance >> 6) * pending.scale;
		} // end for
	} // end for

	textQueue_.clear();
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
} // end of renderText()

void FontView::drawText(const std::string& text, float x, float y, float scale, glm::vec3 color)
{
	textQueue_.push_back(
		{ text, x, y, scale, color }
	);
} // end of drawText()