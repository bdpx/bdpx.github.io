
#define STRICT
#define WINVER 0x0500
#define _WIN32_WINNT 0x0500  /* If not set, assume NT 5.00 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>


/************************************************************************
* Local prototypes
************************************************************************/

static LRESULT CALLBACK
  FrameWndProc(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);
static void InitApplication(HINSTANCE hInstance);

static HWND	wnd_Frame;
static HFONT	Font;
static char	FrameClassName[] = "FrameClassName";


/************************************************************************/
/* This function init toolbar, menu, status bar, */
/* MDI client, all window classes */
/************************************************************************/
static void InitApplication(HINSTANCE hInstance)
{
  RECT		rc;
  WNDCLASS	wc;
  DWORD		dwStyle;

  /* register window classes */
  /* Init frame class */
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = FrameWndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = NULL;
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND+1);
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = FrameClassName;
  RegisterClass(&wc);

  Font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
             ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
             DRAFT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier");

  /* create all windows */
  wnd_Frame = CreateWindow(FrameClassName, "Ex2", WS_OVERLAPPEDWINDOW,
		25, 25, 400, 300, NULL, NULL, hInstance, NULL);

  ShowWindow(wnd_Frame, SW_SHOW);
  UpdateWindow(wnd_Frame);
}

#define DrawTextFormat (DT_LEFT|DT_NOPREFIX|DT_NOCLIP|DT_EXPANDTABS)
static void
DrawWindow(HWND hwnd, HDC hdc)
{
  int	h;
  RECT	r;

//  SetBkColor(hdc, RGB(100,100,100));
  SetBkMode(hdc,TRANSPARENT);
  GetClientRect(hwnd, &r);
  SelectObject(hdc, Font);
  SetTextColor(hdc, RGB(0,55,55));
  DrawText(hdc, "Hello world", -1, &r, DrawTextFormat);
  MoveToEx(hdc, 50, 50, NULL);
  LineTo(hdc, 200, 200);
  MoveToEx(hdc, 50, 200, NULL);
  LineTo(hdc, 200, 50);
}

/************************************************************************
* This function handle main window messages
************************************************************************/
static LRESULT CALLBACK
FrameWndProc(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  PAINTSTRUCT	ps;

  switch (uMessage) {

    case WM_PAINT:
      DrawWindow(hwnd, BeginPaint(hwnd, &ps));
      EndPaint(hwnd, &ps);
      return (0);

    case WM_CREATE:
      return(0);

    case WM_DESTROY:
      PostQuitMessage(0);
      return(0);

    default:
      return(DefWindowProc(hwnd, uMessage, wparam, lparam));
  }
}


/************************************************************************
* This function is entry point
************************************************************************/
#pragma argsused
int APIENTRY
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  MSG		msg;


  InitApplication(hInstance);

  while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
  }

  return(msg.wParam);
}
