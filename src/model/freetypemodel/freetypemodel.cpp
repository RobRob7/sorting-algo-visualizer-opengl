//#include "freetypemodel.h"
//
////--- PUBLIC ---//
//FreeTypeModel::FreeTypeModel()
//{
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft))
//	{
//		std::cout << "ERROR::FREETYPE: Could not init FreeType Library!" << std::endl;
//	}
//	if (FT_New_Face(ft, "../../../res/font/arial.ttf", 0, &face_))
//	{
//		std::cout << "ERROR::FREETYPE: Failed to load font!" << std::endl;
//	}
//	// define pixel font size (face, width, height)
//	// width = 0 (dynamic width sizing)
//	FT_Set_Pixel_Sizes(face_, 0, 48);
//
//	if (FT_Set_Pixel_Sizes(face_, 'X', FT_LOAD_RENDER))
//	{
//		std::cout << "ERROR::FREETYPE: Failed to load Glyph!" << std::endl;
//	}
//
//
//} // end of constructor