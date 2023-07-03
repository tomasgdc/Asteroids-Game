#include "Font.h"

//Engine include
#include "Engine.h"

//Other includes
#include <fstream>
#include <cassert>


/*
  Available glyphs. Yes, hard coded.
  Could be readed from text file. For example.
  GlyphData.txt
  First represents texture and second represents glyph:
  textureA .png a;

"gfx/alet.png",
"gfx/blet.png",
"gfx/clet.png",
"gfx/dlet.png",
"gfx/elet.png",
"gfx/flet.png",
"gfx/glet.png",
"gfx/hlet.png",
"gfx/ilet.png",
"gfx/jlet.png",
"gfx/klet.png",
"gfx/llet.png",
"gfx/mlet.png",
"gfx/nlet.png",
"gfx/olet.png",
"gfx/plet.png",
"gfx/qlet.png",
"gfx/rlet.png",
"gfx/slet.png",
"gfx/tlet.png",
"gfx/ulet.png",
"gfx/vlet.png",
"gfx/wlet.png",
"gfx/xlet.png",
"gfx/ylet.png",
"gfx/zlet.png",

"gfx/num0.png",
"gfx/num1.png",
"gfx/num2.png",
"gfx/num3.png",
"gfx/num4.png",
"gfx/num5.png",
"gfx/num6.png",
"gfx/num7.png",
"gfx/num8.png",
"gfx/num9.png",
"gfx/num10.png",

*/


Font::Font()
{

}


Font::~Font()
{

}


void Font::Initialize(const std::string& strFileName, const std::string strGlyphs)
{
	LoadGlyphDataFromFile(strFileName);
	LoadGlyphsTextures(strGlyphs);
}

void Font::LoadGlyphDataFromFile(const std::string& fileName)
{
	std::ifstream in(fileName, std::ifstream::in);

	if (!in.is_open())
	{
		//MessageBox -> Failed to load file
		assert(false && "Could not load text file with glyph data");
		return;
	}

	std::string texture;
	char c;
	while (in >> texture >> c)
	{
		m_mapCharAndTexture.emplace(std::make_pair(c, texture));
	}
}

void Font::LoadGlyphsTextures(const std::string& str)
{
	for (auto& c : str)
	{
		auto iter = m_mapCharAndTexture.find(c);
		if (iter != m_mapCharAndTexture.end())
		{
			void * pTexture = Engine::getInstance().GetRenderer()->VLoadGFX(iter->second.c_str());

			if (pTexture != nullptr)
			{
				m_mapGlyphTextures.emplace(std::make_pair(c, pTexture));
			}
		}
	}
}


void Font::RenderText(const std::string& text, float xcentre, float ycentre, float xadvance, float yadvance, float xsize, float ysize, float rotate_angle_radians, RGBA tint_col_argb)
{
	float x = xcentre;
	float y = ycentre;

	for (auto& c : text)
	{
		const auto iter = m_mapGlyphTextures.find(c);
		if (iter != m_mapGlyphTextures.end())
		{
			void * pTexture = iter->second;
			x += xadvance;
			y += yadvance;

			Engine::getInstance().GetRenderer()->VRenderGFX(pTexture, x, y, xsize, ysize, deg2rad(rotate_angle_radians));
		}
	}
}

void* Font::GetGlyphTexture(char c)
{
	auto iter = m_mapGlyphTextures.find(c);
	if (iter != m_mapGlyphTextures.end())
	{
		return iter->second;
	}
	return nullptr;
}