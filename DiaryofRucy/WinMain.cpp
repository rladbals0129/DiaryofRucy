#include "Stdafx.h"
#include "MainGame.h"


// 전역변수
HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
bool _loadGame = false;

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
void setWindowSize(int x, int y, int width, int height); 

MainGame* _mg;

int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpszCmdParam,
    int       nCmdShow)
{

    _mg = new MainGame;


    _hInstance = hInstance;

  
    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;                                                    // 클래스 여분 메모리 (게임이기 때문에 메모리 여분이 필요없다)
    wndClass.cbWndExtra = 0;                                                    // 윈도우 여분 메모리 ( 동일 )
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);               // 백그라운드 (흰색으로 하겠다)
    wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));      // 마우스 커서 ( 기본 마우스 커서 쓰겠다)
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);                           // 아이콘 ( 윈도우 창 위에 나오는 아이콘 )
    wndClass.hInstance = hInstance;                                             // 윈도우를 소요한 프로그램의 식별자 정보
    wndClass.lpfnWndProc = (WNDPROC)WndProc;                                    // 윈도우 프로시져
    wndClass.lpszClassName = WINNAME;                                             // 클래스 이름(식별자 정보 - 윈도우창 이름)
    wndClass.lpszMenuName = NULL;                                               // 메뉴 이름 (윈도우창 메뉴)
    wndClass.style = CS_HREDRAW | CS_VREDRAW;                                   // 윈도우 스타일 (다시 그리기 정보)

    // assert()를 걸만한 곳
    //HRESULT hr;
    //hr = RegisterClass(&wndClass);
    //assert(SUCCEEDED(hr));


    RegisterClass(&wndClass);
#ifdef FULLSCREEN
    // 디바이스 모드 구조체 (화면 디스플레이 관련 구조체)
    DEVMODE dm;

    ZeroMemory(&dm, sizeof(DEVMODE));
    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;               // 32비트 트루컬러
    dm.dmPanningWidth = 1980;           // 가로
    dm.dmPanningHeight= 1020;           // 세로
    dm.dmDisplayFrequency = 60;         // 주사율 (재생 빈도 60Hz)

    // 필드 설정
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }
#endif 

    _hWnd = CreateWindow
    (
        WINNAME,                // 윈도우 클래스 식별자
        WINNAME,                // 윈도우 타이틀 바 이름
        WINSTYLE,               // 윈도우 스타일 (게임이기 때문에 계속 덮어 씌움)
        WINSTART_X,             // 윈도우 화면 X좌표
        WINSTART_Y,             // 윈도우 화면 Y좌표
        WINSIZE_X,              // 윈도우 화면 가로 크기
        WINSIZE_Y,              // 윈도우 화면 세로 크기 
        NULL,                   // 부모 윈도우 (GetDesktopWindow 도 가능 기본 모니터)
        (HMENU)NULL,            // 메뉴 핸들
        hInstance,              // 인스턴스 지정
        NULL                    // 윈도우의 자식 윈도우를 생성하면 지정하고 그렇지 않다면 NULL을 잡아라 (윈도우창 여러개 생성 가능)
                                //  ㄴ 필요에 의해 사용하기도 하지만 지금은 NULL
    );

    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;


    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        else
        {
            TIMEMANAGER->update(60.f);
            _mg->update();
            _mg->render();
        }
    }


    _mg->release();
    UnregisterClass(WINNAME, hInstance);
    return message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);  
}


void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0,0,width,height };

    // 실제 윈도우 크기 조정
    //AdjustWindowRect() : RECT 구조체, 윈도우 스타일, 메뉴 여부?
    AdjustWindowRect(&rc, WINSTYLE, false);

    // 얻어온 렉트의 정보로 윈도우사이즈 세팅
    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),       // 앞으로 사이즈에서 x,y앞에 c가 붙으면 center 중심이다
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);     // 렌더링 옵션이다 NOZORDER 내꺼 안가리겠다 | NOMOVE 자식있을 때 쓰는거..

}



