#include "TextRenderer.h"

bool TextRenderer::Init(std::string fontFile)
{
	if (FT_Init_FreeType(&m_ft))
	{
		std::cout << "FreeType failed to initialize\n";
		return false;
	}

	// Assume that all fonts are in the /Fonts folder
	std::string filename = "Fonts\\" + fontFile;
	
	if (FT_New_Face(m_ft, filename.c_str(), 0, &m_face))
	{
		std::cout << "Font " << fontFile.c_str() << " failed to load.\n";
		return false;
	}

	FT_Set_Pixel_Sizes(m_face, 0, 24);

	return true;
}