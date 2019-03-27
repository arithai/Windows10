// t3.cpp : Defines the entry point for the application.
//
//New by mikebonray
#include "stdafx.h"
#include "t3.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

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
	LoadString(hInstance, IDC_T3, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_T3));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_T3));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_T3);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

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

HDC hDC;
TEXTMETRIC textMetric;
HFONT   hFont, hOldFont;
int sizeInPpoints, lineHeight;
RECT textRect,tR;
//char *buffer = "Comprimento em pixels desta string!";
char *buffer = "ABCD";
FILE *fp;

int i,j;
		  hDC = GetDC(hWnd);
          sizeInPpoints = MulDiv(10, GetDeviceCaps(hDC, LOGPIXELSY), 72);
//        hFont = CreateFontA(-sizeInPpoints, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "Courier New");
          hFont = CreateFontA(16, 12, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "細明體");
          hOldFont = (HFONT)SelectObject(hDC, hFont);

          GetTextMetrics(hDC, &textMetric);

          lineHeight = textMetric.tmHeight; // character height in current font

          textRect.left = textRect.right = textRect.top = textRect.bottom = 0;
          DrawTextA(hDC, buffer, strlen(buffer), &textRect, DT_CALCRECT);

		  fp=fopen("h:\\test.txt","wt");
          fprintf(fp,"Size of text calculated by DrawText: [%d x %d]\n", textRect.right, textRect.bottom);
          fprintf(fp,"Height of text calculated by GetTextMetrics: %d\n", lineHeight);
		  fclose(fp);

	switch (message)
	{
	case WM_COMMAND:
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
		// TODO: Add any drawing code here...
		tR.left = 20;  tR.right   = tR.left+textRect.left;
		tR.top  = 20;  tR.bottom =  tR.top+textRect.bottom;
        DrawTextA(hDC, buffer, strlen(buffer), &textRect, DT_NOCLIP);
	    fp=fopen("h:\\pixels.txt","wt");
		for(i=0;i<16;i++) {
		  for(j=0;j<12*4;j++) {
			  if(GetPixel(hDC,j,i)==RGB(0xFF,0xFF,0xFF)) fprintf(fp," ");
			  else fprintf(fp,"0");
		  }
		  fprintf(fp,"\n");
		}
		fclose(fp);
{
        RECT rect;
        HBRUSH hBrush;
        HFONT hFont;

            
            //Logical units are device dependent pixels, so this will create a handle to a logical font that is 48 pixels in height.
            //The width, when set to 0, will cause the font mapper to choose the closest matching value.
            //The font face name will be Impact.
            hFont = CreateFont(48,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Impact"));
            SelectObject(hdc, hFont);
            
            //Sets the coordinates for the rectangle in which the text is to be formatted.
            SetRect(&rect, 100,100,700,200);
            SetTextColor(hdc, RGB(255,0,0));
//          DrawText(hdc, TEXT("Drawing Text with Impact"), -1,&rect, DT_NOCLIP);
            DrawTextA(hdc, "DrawTextA Drawing Text with Impact", -1,&rect, DT_NOCLIP);
            

            //Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
            //The width, when set to 20, will cause the font mapper to choose a font which, in this case, is stretched.
            //The font face name will be Times New Roman.  This time nEscapement is at -300 tenths of a degree (-30 degrees)
            hFont = CreateFont(36,20,-300,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Times New Roman"));
            SelectObject(hdc,hFont);
            
            //Sets the coordinates for the rectangle in which the text is to be formatted.
            SetRect(&rect, 100, 200, 900, 800);
            SetTextColor(hdc, RGB(0,128,0));
            DrawText(hdc, TEXT("Drawing Text with Times New Roman"), -1,&rect, DT_NOCLIP);
            
                
            //Logical units are device dependent pixels, so this will create a handle to a logical font that is 36 pixels in height.
            //The width, when set to 10, will cause the font mapper to choose a font which, in this case, is compressed. 
            //The font face name will be Arial. This time nEscapement is at 250 tenths of a degree (25 degrees)
            hFont = CreateFont(36,10,250,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY, VARIABLE_PITCH,TEXT("Arial"));
            SelectObject(hdc,hFont);

            //Sets the coordinates for the rectangle in which the text is to be formatted.
            SetRect(&rect, 500, 200, 1400, 600);
            SetTextColor(hdc, RGB(0,0,255));
            DrawText(hdc, TEXT("Drawing Text with Arial"), -1,&rect, DT_NOCLIP);
            DeleteObject(hFont);            
        }
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
