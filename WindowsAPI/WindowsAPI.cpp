// WindowsAPI.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WindowsAPI.h"

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)

#define MAX_LOADSTRING 100

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
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // GDI+ 초기화
    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput, nullptr);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSAPI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSAPI));

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

    // GDI+ 정리하기
    Gdiplus::GdiplusShutdown(Token);
    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;  //윈도우 프로시저 함수 등록
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSAPI));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL; //MAKEINTRESOURCEW(IDC_WINDOWSAPI); // 메뉴 제거
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    //실제 윈도우 생성
    HWND hWnd = CreateWindowW(szWindowClass,
        L"2D Shooting for GDI+",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,
        //WS_OVERLAPPEDWINDOW 에서 
        //~WS_MAXIMIZEBOX(최대화 버튼 비활성화) 와 ~WS_THICKFRAME(테두리잡고 크기변경 금지)
        1000, 100, // 시작 좌표 (스크린 좌표계)
        1000, 1000,  // 크기
        nullptr, nullptr, hInstance, nullptr);

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
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    Gdiplus::Graphics GraphicsInstance(hdc);
    Gdiplus::SolidBrush BlueBrush(Gdiplus::Color(255, 0, 0, 255));
    static int x = 150, y = 50;
    Gdiplus::Point points[4] = { Gdiplus::Point(y - 50,x), Gdiplus::Point(y + 50,x - 100),Gdiplus::Point(y + 150,x - 100),Gdiplus::Point(y + 250,x) };
    static bool flag = false;
    switch (message)
    {

    case WM_PAINT:
    {
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        // Graphics 객체 만들기

        GraphicsInstance.FillRectangle(&BlueBrush, y, x, 200, 100);
        GraphicsInstance.FillPolygon(&BlueBrush, points, 4);

        //Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        //GraphicsInstance.FillEllipse(&RedBrush, 200, 50, 60, 60);

        //GraphicsInstance.FillEllipse(&BlueBrush, 0, 50, 60, 60);

        //for (int i = 0; i < 200; i += 15)
        //{
        //    GraphicsInstance.FillRectangle(&RedBrush, i, 200, 10, 10);
        //}

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_KEYDOWN:
        if (flag) {
            return 0;
        }
        flag = true;
        switch (wParam)
        {
        case VK_LEFT:
            OutputDebugStringW(L"왼쪽 누름\n");
            y -= 50;
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        case VK_RIGHT:
            OutputDebugStringW(L"오른쪽 누름\n");
            y += 50;
            InvalidateRect(hWnd, nullptr, TRUE);  // 창을 다시 그리도록 요청(WM_PAINT 메시지가 들어간다)
            break;
        case VK_UP:
            OutputDebugStringW(L"위쪽 누름\n");
            x -= 50;
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        case VK_DOWN:
            OutputDebugStringW(L"아래쪽 누름\n");
            x += 50;
            InvalidateRect(hWnd, nullptr, TRUE);
            break;
        case VK_ESCAPE:
            DestroyWindow(hWnd); // hWnd 창을 닫아라 -> 프로그램을 꺼라(WM_DESTROY메시지가 들어간다.)
            break;
        }
        break;
    case WM_KEYUP:
        flag = false;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
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
