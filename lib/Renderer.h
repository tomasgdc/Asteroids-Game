#pragma once

#ifndef _DIRECT_3D_INCLUDE_H_
#define _DIRECT_3D_INCLUDE_H_
	#pragma warning(disable:4995)
	#pragma warning(disable:4244)
	#include <d3d9.h>
	#include <d3dx9.h>
#endif


#include "IRenderer.h"

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

class Renderer: public IRenderer
{
	friend class Engine;

public:
	Renderer();
	~Renderer();
	
	//Returns true if was initialized succesfully, otherwise returns false
	bool  VInitialize(HWND hWnd, int iScreenWidth, int iScreenHeight);

	//Texture loading (png)
	void* VLoadGFX(const char *fname);

	//Spirte rendering
	void  VRenderGFX(void *sprite, float xcentre, float ycentre, float xsize, float ysize, float rotate_angle_radians = 0, RGBA tint_col_argb = 0xffffffff);

	//Draws simple triangle. Use for debugging purposes.
	void DrawRectangular(float x, float y, float width, float height);
	void DrawRectangular(float xcentre, float ycentre, float xsize, float ysize, float angle);

	//Draw Line
	void DrawLine(float x0, float y0, float x1, float y1);

	void StartFrame();
	void EndFrame();
private:
	//		 Creates a vertex buffer and fills it with our tea2. The vertex
	//       buffer is basically just a chuck of memory that holds tea2. After
	//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
	//       also uses index buffers. The special thing about vertex and index
	//       buffers is that they can be created in device memory, allowing some
	//       cards to process them in hardware, resulting in a dramatic
	//       performance gain.
	HRESULT InitVB();

	//Releases resources
	void Cleanup();

	//Initializes Direct3D
	HRESULT InitD3D(HWND hWnd);
private:
	// A structure for our custom vertex type
	struct CUSTOMVERTEX
	{
		FLOAT x, y, z, rhw; // The transformed position for the vertex
		RGBA color;        // The vertex color
		float u, v;
	};

private:
	LPDIRECT3DDEVICE9       m_pD3DDevice;	// Our rendering device
	LPDIRECT3D9             m_pD3D;			// Used to create the D3DDevice
	LPDIRECT3DVERTEXBUFFER9 m_pVB;			// Buffer to hold tea2		

	int						m_iScreenWidth;
	int						m_iScreenHeight;

	bool					m_bFullscreen;
	bool					m_bCleaned;

};