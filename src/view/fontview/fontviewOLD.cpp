//#include "fontview.h"
//
////--- PUBLIC ---//
//FontView::FontView(int width, int height)
//	: textShader_("../../../res/shader/font/shader.vert", "../../../res/shader/font/shader.frag"),
//	width_(width), height_(height)
//{
//	// enable blending
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//} // end of constructor
//
//FontView::~FontView()
//{
//	if (vao_) glDeleteVertexArrays(1, &vao_);
//	if (vbo_) glDeleteBuffers(1, &vbo_);
//} // end of destructor
//
//void FontView::load(const std::string& fontFileName)
//{
//	// clear previous characters data
//	characters_.clear();
//
//	// initialize FreeType
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft))
//	{
//		std::cerr << "ERROR::FREETYPE: Could not init FreeType Library!\n";
//		return;
//	}
//
//	// load font
//	FT_Face face;
//	std::string fullPath = "../../../font/" + fontFileName;
//	if (FT_New_Face(ft, fullPath.c_str(), 0, &face))
//	{
//		std::cerr << "ERROR::FREETYPE: Failed to load font!\n";
//		FT_Done_FreeType(ft);
//		return;
//	}
//
//	// define pixel font size (face, width, height)
//	// width = 0 (dynamic width sizing)
//	FT_Set_Pixel_Sizes(face, width_, height_);
//
//	// no byte-alignment restriction
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	for (unsigned char c = 0; c < 128; ++c)
//	{
//		// load character glyph
//		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
//		{
//			std::cerr << "ERROR::FREETYPE: Failed to load Glyph!";
//			continue;
//		}
//
//		// generate texture
//		unsigned int texture;
//		glGenTextures(1, &texture);
//		glBindTexture(GL_TEXTURE_2D, texture);
//		glTexImage2D(
//			GL_TEXTURE_2D,
//			0,
//			GL_RED,
//			face->glyph->bitmap.width,
//			face->glyph->bitmap.rows,
//			0,
//			GL_RED,
//			GL_UNSIGNED_BYTE,
//			face->glyph->bitmap.buffer
//		);
//
//		// set texture options
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//		// now store character for later use
//		Character character = {
//			texture,
//			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
//			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
//			face->glyph->advance.x
//		};
//		characters_.insert(std::pair<char, Character>(c, character));
//	} // end for
//
//	// clear FreeType resources
//	FT_Done_Face(face);
//	FT_Done_FreeType(ft);
//} // end of Load()
//
//void FontView::renderText(const std::string& text, float x, float y, float scale, glm::vec3 color)
//{
//
//} // end of renderText()