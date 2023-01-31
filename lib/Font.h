#pragma once

#ifndef _DIRECT_3D_INCLUDE_H_
#define _DIRECT_3D_INCLUDE_H_
	#pragma warning(disable:4995)
	#pragma warning(disable:4244)
	#include <d3d9.h>
	#include <d3dx9.h>
#endif

#include "IRenderer.h"
#include <unordered_map>

/*
	
*/
class Font
{
public:
	Font();
	~Font();


	/*
		@param: const std::string& strFileName - File location that has texture and character connection
		@param: const std::string strGlyphs	   - Specificy what kind of character you want to load into the system memory.
	*/
	void Initialize(const std::string& strFileName, const std::string strGlyphs);

	void RenderText(const std::string& text, float xcentre, float ycentre, float xadvance, float yadvance, float xsize, float ysize, float rotate_angle_radians = 0, RGBA tint_col_argb = 0xffffffff);

	/*
		Returns texture for given character. If not found, will return nullptr
	*/
	void* GetGlyphTexture(char c);

protected:
	/*
		Firstly you have to load glyph text file that represents connection between texture and character.
	*/
	void LoadGlyphDataFromFile(const std::string& fileName);

	/*
		When connection between glyph texture and character is loaded. You can load texture for specific character.
	*/
	void LoadGlyphsTextures(const std::string& str);

private:
	std::unordered_map<char, std::string>	m_mapCharAndTexture;
	std::unordered_map<char, void*>			m_mapGlyphTextures;
};