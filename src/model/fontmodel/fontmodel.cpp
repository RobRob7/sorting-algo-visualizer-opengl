#include "fontmodel.h"

//--- PUBLIC ---//
FontModel::FontModel(const std::string& fontFileName, unsigned int fontWidth, unsigned int fontHeight)
	: width_(fontWidth), height_(fontHeight)
{
	// clear previous characters data
	characters_.clear();

	// initialize FreeType
	if (FT_Init_FreeType(&ft_))
	{
		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library!";
		return;
	}

	// load font
	std::string fullPath = std::string(RESOURCES_PATH) + "font/" + fontFileName;
	if (FT_New_Face(ft_, fullPath.c_str(), 0, &face_))
	{
		std::cerr << "ERROR::FREETYPE: Failed to load font!";
		return;
	}

	// define pixel font size (face_, width_, height_)
	// width = 0 (dynamic width sizing)
	FT_Set_Pixel_Sizes(face_, width_, height_);

	for (unsigned char c = 0; c < 128; ++c)
	{
		// load character glyph
		if (FT_Load_Char(face_, c, FT_LOAD_RENDER))
		{
			std::cerr << "ERROR::FREETYPE: Failed to load Glyph!";
			continue;
		}

		// now store character for later use
		Character character;
		character.size = { face_->glyph->bitmap.width, face_->glyph->bitmap.rows };
		character.bearing = { face_->glyph->bitmap_left, face_->glyph->bitmap_top };
		character.advance = face_->glyph->advance.x;

		character.bitmap.assign(
			face_->glyph->bitmap.buffer,
			face_->glyph->bitmap.buffer + (character.size[0] * character.size[1]));

		// insert into characters_
		characters_.insert(std::pair<char, Character>(c, character));
	} // end for
} // end constructor

FontModel::~FontModel()
{
	// clear FreeType resources
	FT_Done_Face(face_);
	FT_Done_FreeType(ft_);
} // end destructor

const std::map<char, Character>& FontModel::getCharacters() const
{
	return characters_;
} // end of getCharacters()
