// playlistMerge.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <Windows.h>
#include <commdlg.h>
#include "playlistMerge.h"
#include <string>
#define MAX_LOADSTRING 100
#define FILE_OPEN_1 10
#define FILE_OPEN_2 11
#define FILE_PATH_1 12
#define FILE_PATH_2 13
#define MERGE_FILES 14


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Done(HWND, UINT, WPARAM, LPARAM);
int buttonW = 100,buttonH = 40;
int baseX = 30, baseY = 20;

int winWidth = 1000;
int winHeight = 300;


//------------------------------------------------------------------------------------------------
std::string BrowseToFile(HWND hWnd, LPCTSTR filename)
{
    OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HWND hwnd;              // owner window
	HANDLE hf;              // file handle

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = "Text\0*.m3u\0";
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST;// | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn)==TRUE) 
	{
		//return std::string(ofn.lpstrFile); 
		 std::string temp = ofn.lpstrFile;
		 return temp;
	}
		/*hf = CreateFile(ofn.lpstrFile, 
						GENERIC_READ,
						0,
						(LPSECURITY_ATTRIBUTES) NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						(HANDLE) NULL);*/
		return "";
}
//------------------------------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PLAYLISTMERGE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PLAYLISTMERGE));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
//------------------------------------------------------------------------------------------------
//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PLAYLISTMERGE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PLAYLISTMERGE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
//------------------------------------------------------------------------------------------------
//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance; // Store instance handle in our global variable
   //hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, winWidth,winHeight, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//------------------------------------------------------------------------------------------------
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		CreateWindowA("BUTTON", "masterFile",  WS_VISIBLE | WS_CHILD,baseX, baseY,   buttonW,buttonH,hWnd,(HMENU)(FILE_OPEN_1),NULL,0);
		CreateWindowA("BUTTON", "addList",     WS_VISIBLE | WS_CHILD,baseX, baseY*4, buttonW,buttonH,hWnd,(HMENU)(FILE_OPEN_2),NULL,0);
		CreateWindowA("BUTTON", "MERGE!!",     WS_VISIBLE | WS_CHILD,baseX, baseY*8, buttonW,buttonH,hWnd,(HMENU)(MERGE_FILES),NULL,0);
		CreateWindow(TEXT("Edit"), TEXT(masterFilePath.c_str()), WS_CHILD | WS_VISIBLE | WS_BORDER, baseX+buttonW+20, baseY, MAX_PATH*8, 20, hWnd, (HMENU)FILE_PATH_1, NULL, NULL);
		CreateWindow(TEXT("Edit"), TEXT(addFilePath.c_str()), WS_CHILD | WS_VISIBLE | WS_BORDER, baseX+buttonW+20, baseY*4, MAX_PATH*8, 20, hWnd, (HMENU)FILE_PATH_2, NULL, NULL);
            
		break;

	case WM_COMMAND:

		//do file open
		if(LOWORD(wParam) == FILE_OPEN_1)
		{
			//use file browser
			masterFilePath = BrowseToFile(hWnd,"C:\\");
			//set the string to what the file broser gave us so we can see it on screen
			SetDlgItemText(hWnd, FILE_PATH_1, TEXT(masterFilePath.c_str()));

			//if we are using a new master file, we need to clear the old data
			masterPlayListEntry.clear();
		}
		if(LOWORD(wParam) == FILE_OPEN_2)
		{
			addFilePath = BrowseToFile(hWnd,"C:\\");
			//set the string to what the file broser gave us so we can see it on screen
			SetDlgItemText(hWnd, FILE_PATH_2, TEXT(addFilePath.c_str()));
		}
		if(LOWORD(wParam) == MERGE_FILES)
		{
			char buffer[MAX_PATH];
			//get the data in the input filed for master file
			GetDlgItemText(hWnd, FILE_PATH_1, buffer, MAX_PATH);
			//fill string with data in text box (incase they typed in a path)
			masterFilePath = (char *)buffer;

			char buffer2[MAX_PATH];
			GetDlgItemText(hWnd, FILE_PATH_2, buffer2, MAX_PATH);
			//fill string with data in text box (incase they typed in a path)
			addFilePath = (char *)buffer2;

			//add the master list first
			if(masterPlayListEntry.empty())
				addEntries(masterFilePath);
			addEntries(addFilePath);

			updatePlaylist(masterFilePath);

			//display finsihed message
			// 6. with sprintf
			char msg[30]; 
			sprintf(msg, "num dupes ignored: %d", numDupes);
			MessageBox(NULL, msg, "Finihsed", MB_OK);

		}

		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//TextOutA(hdc,10,10,"hello world",11);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//------------------------------------------------------------------------------------------------
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
