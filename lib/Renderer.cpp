#include "Renderer.h"
#include <cmath>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

struct Line_Vertex
{
	float x, y, z, rhw;
	unsigned long color;
};

Renderer::Renderer():
	m_bFullscreen(false), m_bCleaned(false),
m_pD3D(nullptr), m_pD3DDevice(nullptr), m_pVB(nullptr)
{

}


Renderer::~Renderer()
{
	//If resources were not cleaned
	if (!m_bCleaned)
	{
		Cleanup();
	}
}

bool Renderer::VInitialize(HWND hWnd, int iScreenWidth, int iScreenHeight)
{
	m_iScreenWidth = iScreenWidth;
	m_iScreenHeight = iScreenHeight;
	
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		return true;
	}
	return false;
}


HRESULT Renderer::InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = !m_bFullscreen;
	d3dpp.SwapEffect = m_bFullscreen ? D3DSWAPEFFECT_FLIP : D3DSWAPEFFECT_DISCARD;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.BackBufferFormat = m_bFullscreen ? D3DFMT_A8R8G8B8 : D3DFMT_UNKNOWN;
	d3dpp.BackBufferWidth = m_iScreenWidth;
	d3dpp.BackBufferHeight = m_iScreenHeight;
	d3dpp.FullScreen_RefreshRateInHz = m_bFullscreen ? 60 : 0;

	//m_pD3DDevice->Reset(d3dpp);
	// Create the D3DDevice
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		return E_FAIL;
	}


	// Device state would normally be set here
	return S_OK;
}

void Renderer::Cleanup()
{
	if (m_pVB != nullptr)
		m_pVB->Release();

	if (m_pD3DDevice != nullptr)
		m_pD3DDevice->Release();

	if (m_pD3D != nullptr)
		m_pD3D->Release();

	m_bCleaned = true;
}

HRESULT Renderer::InitVB()
{
	if (FAILED(m_pD3DDevice->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		D3DUSAGE_DYNAMIC, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return E_FAIL;
	}
	return S_OK;
}


void * Renderer::VLoadGFX(const char *fname)
{
	IDirect3DTexture9 * tex = nullptr;
	D3DXCreateTextureFromFile(m_pD3DDevice, fname, &tex);
	return tex;
}


void Renderer::VRenderGFX(void *sprite, float xcentre, float ycentre, float xsize, float ysize, float angle, RGBA col)
{
	IDirect3DTexture9 *t = (IDirect3DTexture9 *)sprite;
	m_pD3DDevice->SetTexture(0, t);
	float c = cosf(angle);
	float s = sinf(angle);
#define ROTATE(xx,yy) xcentre+(xx)*c+(yy)*s,ycentre+(yy)*c-(xx)*s 
	CUSTOMVERTEX customvertexes[] =
	{
		{ ROTATE(-xsize,-ysize),	0.5f, 1.0f, col, 0,0},
		{ ROTATE(xsize,-ysize),		0.5f, 1.0f, col, 1,0},
		{ ROTATE(-xsize, ysize),	0.5f, 1.0f, col, 0,1},
		{ ROTATE(xsize, ysize),		0.5f, 1.0f, col, 1,1},
	};

	//DrawRectangular(xcentre, ycentre, xsize, ysize, angle);
	//DrawRectangular(xcentre, ycentre, xsize, ysize);

	m_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, customvertexes, sizeof(CUSTOMVERTEX));
}

void Renderer::DrawRectangular(float xcentre, float ycentre, float xsize, float ysize)
{
	LPD3DXLINE line;
	D3DXCreateLine(m_pD3DDevice, &line);

#define SCALE(xx,yy) xcentre+(xx),ycentre+(yy) 
	D3DXVECTOR2 lines[] =
	{
		D3DXVECTOR2(SCALE(-xsize, -ysize)),
		D3DXVECTOR2(SCALE(xsize,-ysize)),

		D3DXVECTOR2(SCALE(xsize,-ysize)),
		D3DXVECTOR2(SCALE(xsize, ysize)),

		D3DXVECTOR2(SCALE(xsize, ysize)),
		D3DXVECTOR2(SCALE(-xsize, ysize)),

		D3DXVECTOR2(SCALE(-xsize, ysize)),
		D3DXVECTOR2(SCALE(-xsize, -ysize))
	};

	line->Begin();
	line->Draw(lines, 8, 0xffb0c7ee);
	line->End();
	line->Release();
}

void Renderer::DrawRectangular(float xcentre, float ycentre, float xsize, float ysize, float angle)
{
	float c = cosf(angle);
	float s = sinf(angle);
#define ROTATE(xx,yy) xcentre+(xx)*c+(yy)*s,ycentre+(yy)*c-(xx)*s 

	LPD3DXLINE line;
	D3DXCreateLine(m_pD3DDevice, &line);
	D3DXVECTOR2 lines[] =
	{
		D3DXVECTOR2(ROTATE(-xsize, -ysize)),
		D3DXVECTOR2(ROTATE(xsize,-ysize)),

		D3DXVECTOR2(ROTATE(xsize,-ysize)),
		D3DXVECTOR2(ROTATE(xsize, ysize)),

		D3DXVECTOR2(ROTATE(xsize, ysize)),
		D3DXVECTOR2(ROTATE(-xsize, ysize)),

		D3DXVECTOR2(ROTATE(-xsize, ysize)),
		D3DXVECTOR2(ROTATE(-xsize, -ysize))
	};

	line->Begin();
	line->Draw(lines, 8, 0xffb0c7ee);
	line->End();
	line->Release();
}


Line_Vertex line[] =
{
	{ 0.0f, 0.0f,	0.5f, 1.0f, 0xffb0c7ee },
	{ 0.0f, 0.0f,	0.5f, 1.0f, 0xffb0c7ee },
};


void Renderer::DrawLine(float x0, float y0, float x1, float y1)
{
	LPD3DXLINE line;
	D3DXCreateLine(m_pD3DDevice, &line);

	D3DXVECTOR2 lines[] =
	{
		D3DXVECTOR2(x0, y0),
		D3DXVECTOR2(x1, y1)
	};

	line->Begin();
	line->Draw(lines, 2, 0xffb0c7ee);
	line->End();
	line->Release();
}

 void Renderer::StartFrame()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	m_pD3DDevice->BeginScene();
}

 void Renderer::EndFrame()
{
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
