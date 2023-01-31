#pragma once


#ifndef _WINDOW_INCLUDE_H_
#define _WINDOW_INCLUDE_H_
	#include <windows.h>
#endif


typedef unsigned long RGBA;
class IRenderer
{
public:

	//Returns true if was initialized succesfully, otherwise returns false
	virtual bool  VInitialize(HWND hWnd, int iScreenWidth, int iScreenHeight) = 0;

	//Texture loading (png)
	virtual void* VLoadGFX(const char *fname) = 0;

	//Sprite rendering
	virtual void  VRenderGFX(void *sprite, float xcentre, float ycentre, float xsize, float ysize, float rotate_angle_radians = 0, RGBA tint_col_argb = 0xffffffff) = 0;
};