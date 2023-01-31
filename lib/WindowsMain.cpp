
//Project Includes
#include "Engine.h"
#include "AudioComponent.h"
#include "Renderer.h"


//Other includes
#include "lib.h"
#include <math.h>
#include <direct.h>
#include <malloc.h>

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
bool g_keydown[256];
int g_keyhit[256];
int g_mb;
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
	case WM_LBUTTONDOWN:
		SetCapture(hWnd);
		g_mb|=1;
		g_keydown[VK_LBUTTON]=true;
		g_keyhit[VK_LBUTTON]++;
		break;
	case WM_RBUTTONDOWN:
		SetCapture(hWnd);
		g_keydown[VK_RBUTTON]=true;
		g_keyhit[VK_RBUTTON]++;
		g_mb|=2;
		break;
	case WM_MBUTTONDOWN:
		SetCapture(hWnd);
		g_mb|=4;
		g_keydown[VK_MBUTTON]=true;
		g_keyhit[VK_MBUTTON]++;
		break;
	case WM_LBUTTONUP:
		ReleaseCapture();
		g_mb&=~1;
		g_keydown[VK_LBUTTON]=false;
		break;
	case WM_RBUTTONUP:
		ReleaseCapture();
		g_mb&=~2;
		g_keydown[VK_RBUTTON]=false;
		break;
	case WM_MBUTTONUP:
		ReleaseCapture();
		g_mb&=~4;
		g_keydown[VK_MBUTTON]=false;
		break;
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		g_keydown[wParam&255]=true;
		g_keyhit[wParam&255]++;
		return 0;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		g_keydown[wParam&127]=false;
		break;
    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
	case WM_ACTIVATEAPP:
		if (!wParam)
		{
			memset(g_keydown,0,sizeof(g_keydown));
		}
		break;
	case WM_ACTIVATE:
		if( WA_INACTIVE != wParam )
		{
			// Make sure the device is acquired, if we are gaining focus.
			
		}
		break;
    }
    return DefWindowProc( hWnd, msg, wParam, lParam );
}

void ResetKeys()
{
	memset(g_keydown, 0, sizeof(g_keydown));
	memset(g_keyhit, 0, sizeof(g_keyhit));
}



//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR cmd, INT )
{
	//int id = MessageBox(NULL,"goto fullscreen?","fullscreen mode",MB_YESNOCANCEL);
	//if (id==IDCANCEL) return 0;
	//fullscreen=(id==IDYES);

	Engine::getInstance().SetApplicationName("Asteroids");
	Engine::getInstance().Initialize(800, 600, MsgProc, false);

    GameMain();
    return 0;
}

//////////////////////////////////
bool CheckBegin(RGBA clearcol)
{
	// Enter the message loop
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		if (msg.message==WM_QUIT) return true;
	}

	Engine::getInstance().GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, clearcol, 1.0f, 0 );
	Engine::getInstance().GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
	Engine::getInstance().GetD3DDevice()->SetRenderState(D3DRS_ZENABLE,false);
	Engine::getInstance().GetD3DDevice()->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	Engine::getInstance().GetD3DDevice()->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	Engine::getInstance().GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_DIFFUSE);
	Engine::getInstance().GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLORARG2,D3DTA_TEXTURE);
	Engine::getInstance().GetD3DDevice()->SetTextureStageState(0,D3DTSS_COLOROP,D3DTOP_MODULATE);
	Engine::getInstance().GetD3DDevice()->SetTextureStageState(0,D3DTSS_ALPHAARG1,D3DTA_DIFFUSE);
	Engine::getInstance().GetD3DDevice()->SetTextureStageState(0,D3DTSS_ALPHAARG2,D3DTA_TEXTURE);
	Engine::getInstance().GetD3DDevice()->SetTextureStageState(0,D3DTSS_ALPHAOP,D3DTOP_MODULATE);
	Engine::getInstance().GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	Engine::getInstance().GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
	Engine::getInstance().GetD3DDevice()->SetRenderState(D3DRS_LIGHTING,false);

	//Engine::getInstance().GetD3DDevice()->SetTexture(0,NULL);
	Engine::getInstance().GetD3DDevice()->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	D3DVIEWPORT9 vp = { 0,0, Engine::getInstance().GetWindowsWidth(), Engine::getInstance().GetWindowsHeight(), 0, 1};
	Engine::getInstance().GetD3DDevice()->SetViewport(&vp);
	Engine::getInstance().GetD3DDevice()->SetFVF( D3DFVF_CUSTOMVERTEX );

	// Begin the scene
	//Engine::getInstance().GetD3DDevice()->BeginScene() ;
	//UpdateDirectInput();
	return false;
}



void Flip()
{
	/*
	static int lastflip=0;
	if (lastflip == 0)
	{
		lastflip = Engine::getInstance().GetTimeInMS();
	}
	*/

	//Engine::getInstance().GetD3DDevice()->EndScene();
	// Present the backbuffer contents to the display
	//while (GetTimeInMS()<lastflip+1000/60) ;// Sleep(0); // clamp to max of 60hz

	//lastflip= Engine::getInstance().GetTimeInMS();
	//Engine::getInstance().GetD3DDevice()->Present( NULL, NULL, NULL, NULL );

	Sleep(0);
	memset(g_keyhit,0,sizeof(g_keyhit));
	//SetCursor(LoadCursor(NULL,IDC_ARROW));
}


bool IsKeyDown(int key) // use windows VK_ codes for special keys, eg VK_LEFT; use capital chars for letter keys eg 'A', '0'
{
	return g_keydown[key&255];
}