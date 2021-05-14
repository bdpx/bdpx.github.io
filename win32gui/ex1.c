
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


static LRESULT CALLBACK
  FrameWndProc(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam);
static void InitApplication(HINSTANCE hInstance);

static HWND	wnd_Frame;
static char	FrameClassName[] = "FrameClassName";


/************************************************************************/
/* This function init toolbar, menu, status bar, */
/* MDI client, all window classes */
/************************************************************************/
static void InitApplication(HINSTANCE hInstance)
{
  int		i, k, y, x;
  RECT		rc;
  WNDCLASS	wc;
  DWORD		dwStyle;
  char		buf[200];

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

  wnd_Frame = CreateWindow(FrameClassName, "Ex1", WS_OVERLAPPEDWINDOW,
		25, 25, 400, 300, NULL, NULL, hInstance, NULL);

  ShowWindow(wnd_Frame, SW_SHOW);
  UpdateWindow(wnd_Frame);
}


/************************************************************************
* This function handle main window messages
************************************************************************/
static LRESULT CALLBACK
FrameWndProc(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
  switch (uMessage) {

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
