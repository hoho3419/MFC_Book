// Win32Concave.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Win32Concave.h"

#define MAX_LOADSTRING 100

// 가로, 세로 줄이 19개인 바둑판을 만들어서 사용함
#define X_COUNT           19
#define Y_COUNT           19

// 화면의 왼쪽에서 바둑판의 왼쪽면까지의 거리(여백)
#define START_X           50
// 화면의 위쪽에서 바둑판의 위쪽면까지의 거리(여백)
#define START_Y           50

// 줄 사이의 간격이 26이다. 바둑 돌의 지름 크기도 동일하다.
#define INTERVAL          26
// 바둑 돌의 반지름은 줄 간격의 절반과 동일하다.
#define HALF_INTERVAL     INTERVAL/2

// 바둑판에 돌이 놓일 수 있는 위치를 좀더 편하게 계산할 수 있도록
// 매크로 함수로 만들었다. x와 y에 0 ~ 18 값을 사용하면 
// 실제 화면상의 좌표로 알 수 있다.
#define XPOS(x)   (START_X + (x) * INTERVAL)
#define YPOS(y)   (START_Y + (y) * INTERVAL)

// 바둑판에 돌이 놓여져 있는지 기억하기 위한 변수 배열의 각 항목의 값이 0이면 돌이 
// 놓여져 있지 않다는 뜻이고 1이면 검은색 돌, 2이면 흰색 돌이 놓여져 있다는 뜻이다.
unsigned char g_dol[Y_COUNT][X_COUNT];
// 현재 어떤 돌을 놓을 것인지를 결정하는 변수 (0이면 검은색, 1이면 흰색 돌을 놓을 순서)
unsigned char g_step;

void OnPaint(HWND ah_wnd)
{
    PAINTSTRUCT ps;
    HDC h_dc = BeginPaint(ah_wnd, &ps);

    for (int x = 0; x < X_COUNT; x++) {  // 수직으로 19개의 선을 그린다.
        // (x, 0)점과 (x, Y_COUNT-1)점을 연결하는 선을 그린다.
        MoveToEx(h_dc, XPOS(x), YPOS(0), NULL);
        LineTo(h_dc, XPOS(x), YPOS(Y_COUNT - 1));
    }

    for (int y = 0; y < Y_COUNT; y++) {   // 수평으로 19개의 선을 그린다.
        // (0, y)점과 (X_COUNT - 1, y)점을 연결하는 선을 그린다.
        MoveToEx(h_dc, XPOS(0), YPOS(y), NULL);
        LineTo(h_dc, XPOS(X_COUNT - 1), YPOS(y));
    }

    // 바둑판 전체에 놓여져 있는 돌을 각 위치별로 체크하면서 돌이 놓여져
    // 있으면 돌의 종류에 따라 그린다.
    for (int y = 0; y < Y_COUNT; y++) {
        for (int x = 0; x < X_COUNT; x++) {
            if (g_dol[y][x] > 0) {   // 바둑돌이 놓여져 있는 경우 (1:검은돌, 2:흰돌)
                // 검은돌이면 검은색을 설정하고 흰돌이면 흰색을 설정한다.
                if (g_dol[y][x] == 1) SelectObject(h_dc, GetStockObject(BLACK_BRUSH));
                else SelectObject(h_dc, GetStockObject(WHITE_BRUSH));
                // 바둑돌이 놓여질 위치를 계산한다. (x,y)를 중심점으로 하고 
                // 반지름이 HALF_INTERVAL인 원이 그려질 좌표를 구성한다.
                Ellipse(h_dc, XPOS(x) - HALF_INTERVAL, YPOS(y) - HALF_INTERVAL,
                    XPOS(x) + HALF_INTERVAL, YPOS(y) + HALF_INTERVAL);
            }
        }
    }

    EndPaint(ah_wnd, &ps);
}


void OnLButtonDown(HWND ah_wnd, int a_x, int a_y)
{
    // 바둑판 영역에만 돌을 놓을 수 있도록 터치한 위치가 바둑판 영역인지 체크한다.
    if (a_x > (XPOS(0) - HALF_INTERVAL) && a_y > (YPOS(0) - HALF_INTERVAL)
        && a_x < (XPOS(X_COUNT - 1) + HALF_INTERVAL)
        && a_y < (YPOS(Y_COUNT - 1) + HALF_INTERVAL)) {
        // 터치한 위치에 바둑판의 여백을 빼고 줄 간격으로 나누면 x, y 값이
        // 0 ~ 18의 값을 가지게 된다. 즉, 바둑판의 각 줄의 위치 값을 바로 
        // 얻을 수 있다. 그리고 터치한 위치와 가까운 줄쪽으로 이동할 수 있도록
        // 줄 간격의 절반만큼 더하고 줄간격으로 나누어야 한다. (블로그 설명 참고)
        int x = (a_x - START_X + HALF_INTERVAL) / INTERVAL;
        int y = (a_y - START_Y + HALF_INTERVAL) / INTERVAL;
        if (g_dol[y][x] == 0) {  // 돌이 없는 곳에만 돌을 놓을 수 있다.
            // g_step이 0이면 검은돌이 놓여질 순서이고 1이면 흰돌이 놓여질 순서이기
            // 때문에 g_step에 1을 더해서 바둑판에 놓여진 돌 정보를 구성하면
            // 돌이 없으면 0, 검은돌이면 1, 흰돌이면 2가 저장됩니다.
            g_dol[y][x] = g_step + 1;
            // 검은돌을 놓았으면 흰돌로 상태를 변경하고 
            // 흰돌을 놓았으면 검은돌로 상태를 변경한다.
            g_step = !g_step;
            // 화면을 갱신해서 돌 놓은것을 적용한다.
            InvalidateRect(ah_wnd, NULL, TRUE);
        }
    }
}




// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    /*
    WNDCLASS wc;
    wchar_t my_class_name[] = L"tipssoft";
    // 배경색으로 사용할 브러시를 생성한다.
    HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77));
    wc.cbClsExtra = NULL;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)h_bk_brush;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = my_class_name;
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND h_wnd = CreateWindow(my_class_name, L"www.tipssoft.com - 오목 만들기!",
        WS_OVERLAPPEDWINDOW, 50, 50, 600, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(h_wnd, SW_SHOW);
    UpdateWindow(h_wnd);
    */
    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WIN32CONCAVE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32CONCAVE));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;
    HBRUSH h_bk_brush = CreateSolidBrush(RGB(244, 176, 77));
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32CONCAVE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32CONCAVE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hbrBackground = (HBRUSH)h_bk_brush;

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_PAINT) {
        OnPaint(hWnd);
        return 0;
    }
    else if (message == WM_LBUTTONDOWN) {
        int x = LOWORD(lParam);    // 하위 16비트 값 분리, 마우스가 클릭된 X 좌표
        int y = HIWORD(lParam);    // 상위 16비트 값 분리, 마우스가 클릭된 Y 좌표
        OnLButtonDown(hWnd, x, y);
    }
    else if (message == WM_DESTROY) {
        PostQuitMessage(0);
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
