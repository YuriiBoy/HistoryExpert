
#include "framework.h"
#include "HistoryExpert.h"
#include"EpoqueRepo.h"

#define MAX_LOADSTRING 100

#define IDC_BUTTON_PRIMITIVE_SOCIETY 5001
#define IDC_BUTTON_ANCIENT_WORLD 5002
#define IDC_BUTTON_MIDLE_AGES 5003
#define IDC_BUTTON_NEW_TIME 5004
#define IDC_BUTTON_GET_EPOQUE 5005

//
HWND hButton1, hButton2, hButton3, hButton4, hButton5;
HWND hGetEpoque, hHistoryFramework, hHistoryInfo;

HWND hListEpoque, hEditEpoque, hCorEpoque;

//
TCHAR historyEpoque[100];
auto epoqueRepo = std::make_unique<EpoqueRepo>("Epoque.txt");

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Info(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    EpoqueWindow(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HISTORYEXPERT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HISTORYEXPERT));

    MSG msg;

    // Main message loop:
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
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HISTORYEXPERT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HISTORYEXPERT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // 1 Caption and location of Wnd:
        SetWindowText(hWnd, L"Історичний довідник");
        MoveWindow(hWnd, 300, 150, 500, 330, true);

        // 2 Main controls
        hButton1 = CreateWindowEx(0, L"BUTTON", L"Первісне суспільство", WS_CHILD |
            WS_VISIBLE, 30, 20, 160, 40, hWnd, (HMENU)IDC_BUTTON_PRIMITIVE_SOCIETY,
            hInst, NULL);
        hButton2 = CreateWindowEx(0, L"BUTTON", L"Стародавній світ", WS_CHILD |
            WS_VISIBLE, 30, 80, 160, 40, hWnd, (HMENU)IDC_BUTTON_ANCIENT_WORLD,
            hInst, NULL);
        hButton3 = CreateWindowEx(0, L"BUTTON", L"Середні віки", WS_CHILD |
            WS_VISIBLE, 30, 140, 160, 40, hWnd, (HMENU)IDC_BUTTON_MIDLE_AGES,
            hInst, NULL);
        hButton4 = CreateWindowEx(0, L"BUTTON", L"Новий час", WS_CHILD |
            WS_VISIBLE, 30, 200, 160, 40, hWnd, (HMENU)IDC_BUTTON_NEW_TIME,
            hInst, NULL);
        // * additional controls
        hGetEpoque = CreateWindowEx(0, L"BUTTON", L"Періодизація історії", WS_CHILD |
            WS_VISIBLE, 260, 20, 200, 40, hWnd,
            (HMENU)IDC_BUTTON_GET_EPOQUE, hInst, NULL);
    }
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDC_BUTTON_GET_EPOQUE:
            {
                epoqueRepo->loadData();
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, EpoqueWindow);
            }
            break;
            case IDC_BUTTON_PRIMITIVE_SOCIETY:
            {
                lstrcpy(historyEpoque, L"Первісне суспільство");
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Info);
            }
            break;
            case IDC_BUTTON_ANCIENT_WORLD:
            {
                lstrcpy(historyEpoque, L"Стародавній світ");
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Info);
            }
            break;
            case IDC_BUTTON_MIDLE_AGES:
            {
                lstrcpy(historyEpoque, L"Середні віки");
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Info);
            }
            break;
            case IDC_BUTTON_NEW_TIME:
            {
                lstrcpy(historyEpoque, L"Новий час");
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Info);
            }
            break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

INT_PTR CALLBACK Info(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
         
        TCHAR  buff[100];
        lstrcpy(buff, L"Information Window -");
        lstrcat(buff, historyEpoque);
        SetWindowText(hDlg, buff);
        //
        hHistoryFramework = GetDlgItem(hDlg, IDC_LIST1); 
        hHistoryInfo = GetDlgItem(hDlg, IDC_EDIT1);

    }
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

INT_PTR CALLBACK EpoqueWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        // 2
        hListEpoque = GetDlgItem(hDlg, IDC_LIST1);
        hEditEpoque = GetDlgItem(hDlg, IDC_EDIT1);
        hCorEpoque = GetDlgItem(hDlg, IDC_BUTTON1);
        //
        for (auto& epoq : epoqueRepo->getEpoque()) {
            SendMessage(hListEpoque, LB_ADDSTRING, 0, LPARAM(epoq.getName()));
        }

    }
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