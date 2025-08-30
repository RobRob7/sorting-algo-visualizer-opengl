#ifndef FONTMODEL_H
#define FONTMODEL_H

#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

struct Character
{
	// bitmap (raw grayscale pixels)
	std::vector<unsigned char> bitmap;
	// size of glyph
	glm::ivec2 size;
	// offset from baseline to left/top of glyph
	glm::ivec2 bearing;
	// offset to advance to next glyph
	unsigned int advance;
};

class FontModel
{
public:
	FontModel(const std::string& filePath, unsigned int width, unsigned int height);
	~FontModel();

	const std::map<char, Character>& getCharacters() const;

private:
	// font width, height
	unsigned int width_;
	unsigned int height_;
	// FreeType
	FT_Library ft_;
	FT_Face face_;
	// map of characters
	std::map<char, Character> characters_;
};

#endif