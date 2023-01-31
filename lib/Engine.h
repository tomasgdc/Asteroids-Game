#pragma once
#include "Helpers.h"
#include <string>
#include <chrono>

//Renderer
#include "Renderer.h"

//Forward declaration
class AudioComponent;
class Renderer;
class EventManager;
class SceneManager;
class SoundManager;

class Engine: public Singleton<Engine>
{
public:
	Engine();
	~Engine();

	void SetApplicationName(const std::string& strName) { m_strApplicationName = strName; }
	void Initialize(int WindowWidth, int WindowsHeight, LRESULT(CALLBACK MainWindowProc)(HWND, UINT, WPARAM, LPARAM), bool bFullscreen = false);
	void Shutdown();

	//Main frame logic
	void Frame();

	//Returns Direct3D device
	LPDIRECT3DDEVICE9 GetD3DDevice() { return m_pRenderer->m_pD3DDevice; }

	//Get components
	Renderer* GetRenderer() { return m_pRenderer; }
	EventManager* GetEventManager() { return m_pEventManager; }
	SceneManager* GetSceneManager() { return m_pSceneManager; }
	SoundManager* GetSoundManager() { return m_pSoundManager; }

	//Miscellaneous
	void GetMousePos(float &x, float &y); // 0,0 is top left;,600 is bottom right 
	int GetWindowsHeight() { return m_iScreenHeight; }
	int GetWindowsWidth() { return m_iScreenWidth; }
	int	GetTimeInMS();

	//Chorno timer
	void StartTimer();
	double EndTimer();

private:
	std::string		m_strApplicationName;

	//Timer
	LARGE_INTEGER	m_StartTime;
	LARGE_INTEGER	m_Freq;

	//Chrono timer
	std::chrono::high_resolution_clock::time_point m_chornoNow;
	std::chrono::high_resolution_clock::time_point m_chornoEnd;

	//Screen size
	int  m_iScreenWidth;
	int  m_iScreenHeight;

	//Windows
	HWND			m_hWnd;
	WNDCLASSEX		m_wc;

	//Components
	Renderer*		m_pRenderer;
	AudioComponent* m_pAudioComponent;
	EventManager*	m_pEventManager;
	SceneManager*	m_pSceneManager;
	SoundManager*	m_pSoundManager;
	

	bool			m_bInitialized;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//		MATH 
#include <math.h>
#define PI ((float)3.1415926535)
#define DEG2RAD ((float)0.0174533)
#define RAD2DEG ((float)57.29577951308233)
inline float deg2rad(float d) 
{
	return d * DEG2RAD;	// PI/180
}
inline float rad2deg(float r) 
{
	return r * RAD2DEG;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////