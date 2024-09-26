
#pragma once

#pragma warning(disable: 4005)

#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN 

#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")

#pragma comment (lib, "lib/FMOD/fmodex_vc.lib")

#pragma comment (lib, "Jsoncpp/lib_json/json_vc71_libmtd.lib")

#pragma comment (lib, "msimg32.lib")

#include "inc/FMOD/fmod.hpp"
#include "Jsoncpp/Include/json.h"
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>




#include <iostream>
#include <chrono>
#include <random>
#include <vector>
#include <map>
#include <unordered_map>
#include <cassert>
#include <functional>
#include <fstream>
#include <queue>
#include <deque>
#include <bitset>

using namespace std;

#include <d2d1.h>
#include <wincodec.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

#include "resource.h"
#include "CommonMacroFunction.h" 
#include "RandomFunction.h"  
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "D2DImageManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "INIData.h"
#include "JsonSaveLoader.h"

using namespace MY_UTIL;
using namespace OBB_COLLISION;


#define RND				 RandomFunction::getSingleton()
#define KEYMANAGER		 KeyManager::getSingleton()
#define IMAGEMANAGER	 ImageManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define FONTMANAGER		 FontManager::getSingleton()
#define D2DMANAGER       D2DImageManager::getSingleton()
#define TIMEMANAGER      TimeManager::getSingleton()
#define SCENEMANAGER	 SceneManager::getSingleton()
#define SOUNDMANAGER	 SoundManager::getSingleton()
#define INIDATAMANAGER	 INIData::getSingleton()
#define JSONDATAMANAGER  JsonSaveLoader::getSingleton()

#define WINNAME			(LPTSTR)(TEXT("WindowsAPI"))
#define MAGENTA			RGB(255,0,255)


//#define FULLSCREEN
#ifdef FULLSCREEN //FULLSCREEN

#define WINSTART_X		0
#define WINSTART_Y		0
//GetSystemMetrics() : 인자로 전달되는 시스템 설정 정보를 반환
// ㄴ SM_CXSCREEN / SM_CYSCREEN  = 현재 화면 해상도 X / Y 축 반환
#define WINSIZE_X		GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y		GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE		WS_POPUPWINDOW | WS_MAXIMIZE


#else
// # 매크로 # (윈도우창 초기화)
#define WINSTART_X		200
#define WINSTART_Y		100
#define WINSIZE_X		1280
#define WINSIZE_Y		720
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

#endif // FULLSCREEN




// WS_CAPTION : 타이틀 바를 가지기 위한 옵션
// WS_SYSMENU : 제목 표시줄에 콘트롤 메뉴 상자 창

// # 매크로 함수 #  ( 클래스에서 동적할당된 부분을 해제할 때 사용)
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}
#define SAFE_RELEASE_SCENE(p)	{if(p) {(p)->Release(); (p) = nullptr;}}

// # 전역 변수 #
// extern 키워드는 다른 헤더 / cpp에서 변수를 공유해서 쓰기 위해 사용한다.
//  ㄴ 객체를 주로 써라
// 기본적으로 전역변수는 키워드를 생략해도 기본적으로 extern화 되는 경우가 많다.
extern HINSTANCE		_hInstance;
extern HWND				_hWnd;
// X 좌표와 Y좌표를 평면의 좌표에 정의할 때 사용한다
extern POINT			_ptMouse; // 어디에서도 사용가능해서 전역에 쓰기 좋다
//extern int				_changeGame;
//extern ID2D1HwndRenderTarget* _ID2DRenderTarget = nullptr; // 대상객체가 모호해서(null로 날려버려서) extern화 안될 수 있다

extern bool				_loadGame;
