#include "Engine.h"

//Renderer Includes
#include "Renderer.h"

//Event Manager
#include "EventManager.h"

//Sound Includes
#include "AudioComponent.h"
#include "fmod/api/inc/fmod.h"

//SceneManager
#include "SceneManager.h"

//SoundManager
#include "SoundManager.h"

//Other includes
#include <string>

Engine::Engine():m_bInitialized(false)
{
	m_strApplicationName = "Set name for application";
}

Engine::~Engine()
{
	Shutdown();
}

void Engine::Initialize(int WindowWidth, int WindowsHeight, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM), bool bFullscreen)
{
	m_iScreenWidth = WindowWidth;
	m_iScreenHeight = WindowsHeight;

	//Initialize Windows
	WNDCLASSEX wc = 
	{ 
		sizeof(WNDCLASSEX), 
		CS_CLASSDC, 
		MainWindowProc, 
		0L, 
		0L,
		GetModuleHandle(NULL), 
		NULL, 
		NULL, 
		NULL, 
		NULL,
		m_strApplicationName.c_str(),
		NULL 
	};
	RegisterClassEx(&wc);

	//Initialize FMOD
	//44100 Hz
	FSOUND_Init(44100, 42, 0);

	RECT r = { 0, 0, WindowWidth, WindowsHeight };
	int style = bFullscreen ? WS_POPUP : WS_OVERLAPPEDWINDOW;
	style |= WS_VISIBLE;
	AdjustWindowRect(&r, style, false);

	// Create the application's window
	m_hWnd = CreateWindow(
		m_strApplicationName.c_str(),
		m_strApplicationName.c_str(),
		style, 
		0, 
		0, 
		r.right - r.left,
		r.bottom - r.top,
		GetDesktopWindow(),
		NULL, 
		wc.hInstance,
		NULL
	);

	//Initialize QueryPerfomance counter
	QueryPerformanceCounter(&m_StartTime);
	QueryPerformanceFrequency(&m_Freq);

	//Initialize Subsystem
	m_pRenderer = new Renderer;
	m_pAudioComponent = new AudioComponent;
	m_pEventManager = new EventManager;
	m_pSceneManager = new SceneManager;
	m_pSoundManager = new SoundManager;

	// Initialize Renderer
	if(m_pRenderer->VInitialize(m_hWnd, WindowWidth, WindowsHeight));
	{
		// Create the vertex buffer
		//if( SUCCEEDED( InitVB() ) )
		{
			//SetWindowPos(hWnd,NULL,0,0,1024,768,SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOMOVE|SWP_ASYNCWINDOWPOS);
			ShowCursor(false);
			SetCursor(LoadCursor(NULL, IDC_ARROW));

			// Show the window
			ShowWindow(m_hWnd, SW_SHOWDEFAULT);
			UpdateWindow(m_hWnd);

			//InitDirectInput( hWnd );			
			//GameMain();
		}
	}

	//Everything is initialized
	m_bInitialized = true;
}

void Engine::Frame()
{

	
}

void Engine::Shutdown()
{
	if (m_bInitialized)
	{
		//The order of deletion is important

		delete m_pSceneManager;
		m_pSceneManager = nullptr;

		delete m_pAudioComponent;
		m_pAudioComponent = nullptr;

		delete m_pRenderer;
		m_pRenderer = nullptr;

		delete m_pEventManager;
		m_pEventManager = nullptr;

		delete m_pSoundManager;
		m_pSoundManager = nullptr;

		UnregisterClass(m_strApplicationName.c_str(), m_wc.hInstance);
	}
}

int Engine::GetTimeInMS()
{
	LARGE_INTEGER ms;
	QueryPerformanceCounter(&ms);
	return ((ms.QuadPart - m_StartTime.QuadPart) * 1000) / m_Freq.QuadPart;
}

void Engine::StartTimer()
{
	m_chornoNow = std::chrono::high_resolution_clock::now();
}

double Engine::EndTimer()
{
	m_chornoEnd = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<std::chrono::microseconds>(m_chornoEnd - m_chornoNow).count();
}

void Engine::GetMousePos(float &x, float &y)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(m_hWnd, &p);
	x = p.x;
	y = p.y;
}