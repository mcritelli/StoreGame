#ifndef TEXTRENDERER_H
#define TEXTRENDERER_H


#include <..\freetype\ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
using namespace std;

class TextRenderer{
public:
	bool Init(std::string);
private:
	FT_Library m_ft;
	FT_Face m_face;
};


#endif