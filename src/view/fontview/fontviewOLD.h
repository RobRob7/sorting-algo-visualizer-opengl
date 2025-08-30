//#ifndef FONTVIEW_H
//#define FONTVIEW_H
//
//#include "../shader/shader.h"
//
//#include <ft2build.h>
//#include FT_FREETYPE_H
//#include <glm/glm.hpp>
//
//#include <iostream>
//#include <map>
//
//struct Character
//{
//	// ID of glyph texture
//	unsigned int textureID;
//	// size of glyph
//	glm::ivec2 size;
//	// offset from baseline to left/top of glyph
//	glm::ivec2 bearing;
//	// offset to advance to next glyph
//	unsigned int advance;
//};
//
//class FontView
//{
//public:
//	FontView(int width, int height);
//	~FontView();
//	// for each character, generate a texture and store data
//	// in Character
//	void load(const std::string& fontFileName);
//	// 
//	void renderText(const std::string& text, float x, float y, float scale, glm::vec3 color);
//
//private:
//	// font width, height
//	unsigned int width_;
//	unsigned int height_;
//	// map of characters to render
//	std::map<char, Character> characters_;
//	// font VAO
//	unsigned int vao_;
//	// font VBO
//	unsigned int vbo_;
//	// shader for font rendering
//	Shader textShader_;
//};
//
//#endif
