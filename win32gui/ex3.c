
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

enum {
	CM_OPEN = 1001,
	CM_EXIT,
	CM_START,
	CM_STEP,
	CM_STOP,
	CM_LINEUP,
	CM_LINEDOWN,
	CM_PAGEUP,
	CM_PAGEDOWN,
	CM_END,
	CM_HOME,
};


/************************************************************************/
/* This function init toolbar, menu, status bar, */
/* MDI client, all window classes */
/************************************************************************/
static void InitApplication(HINSTANCE hInstance)
{
  int		i, k, y, x;
  HWND		child;
  RECT		rc;
  HMENU		menu, popup;
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

  Font = CreateFont(14, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
             ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
             DRAFT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Courier");

  menu = CreateMenu();
  popup = CreatePopupMenu();
  InsertMenu(popup, -1, MF_BYPOSITION|MF_STRING, CM_OPEN, "Open");
  InsertMenu(popup, -1, MF_BYPOSITION|MF_SEPARATOR, 0, NULL);
  InsertMenu(popup, -1, MF_BYPOSITION|MF_STRING, CM_EXIT, "Exit");
  InsertMenu(menu,  -1, MF_BYPOSITION|MF_POPUP, (UINT)popup, "Popup1");
  popup = CreatePopupMenu();
  InsertMenu(popup, -1, MF_BYPOSITION|MF_STRING, CM_START, "Start");
  InsertMenu(popup, -1, MF_BYPOSITION|MF_STRING, CM_STEP, "Step");
  InsertMenu(popup, -1, MF_BYPOSITION|MF_STRING, CM_STOP, "Stop");
  InsertMenu(menu,  -1, MF_BYPOSITION|MF_POPUP, (UINT)popup, "Popup2");

  /* create all windows */
  wnd_Frame = CreateWindow(FrameClassName, "Ex3", WS_OVERLAPPEDWINDOW,
		25, 25, 400, 300, NULL, menu, hInstance, NULL);

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
  int		CmdId, value;
  HWND		child;
  PAINTSTRUCT	ps;

  switch (uMessage) {

    case WM_PAINT:
      DrawWindow(hwnd, BeginPaint(hwnd, &ps));
      EndPaint(hwnd, &ps);
      return (0);

    case WM_COMMAND:
      CmdId = GET_WM_COMMAND_ID(wparam, lparam);
      switch(CmdId) {
        case CM_OPEN:
          MessageBox(hwnd, "Open", "Open", MB_OK);
          break;
        case CM_EXIT:
          PostMessage(hwnd, WM_QUIT, 0, 0);
          break;

        default:
          return(DefWindowProc(hwnd, uMessage, wparam, lparam));
      }
      return(0);

    case WM_MOUSEWHEEL:
      return(0);

    case WM_VSCROLL:
      value = GetScrollPos(hwnd, SB_VERT);
      switch (GET_WM_VSCROLL_CODE(wparam,lparam)) {
        case SB_TOP:            value = 0; break;
        case SB_BOTTOM:         value = 255;  break;
        case SB_LINEUP:         value = value - 1;   break;
        case SB_LINEDOWN:       value = value + 1;   break;
        case SB_PAGEUP:         value = value - 20;  break;
        case SB_PAGEDOWN:       value = value + 20;  break;
        case SB_THUMBTRACK:     value = GET_WM_VSCROLL_POS(wparam,lparam);  break;
        case SB_THUMBPOSITION:  value = GET_WM_VSCROLL_POS(wparam,lparam);  break;
      }
      return (0);

    case WM_CREATE:
      return(0);

    case WM_DESTROY:
      PostMessage(hwnd, WM_QUIT, 0, 0);
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
  HACCEL	Accel;


  static ACCEL AccelTable[] = {
	{ FVIRTKEY,		VK_UP,		CM_LINEUP	},
	{ FVIRTKEY,		VK_DOWN,	CM_LINEDOWN	},
	{ FVIRTKEY,		VK_PRIOR,	CM_PAGEUP	},
	{ FVIRTKEY,		VK_NEXT,	CM_PAGEDOWN	},
	{ FVIRTKEY|FCONTROL,	VK_END,		CM_END		},
	{ FVIRTKEY|FCONTROL,	VK_HOME,	CM_HOME		},
  };


  InitApplication(hInstance);

  Accel = CreateAcceleratorTable(AccelTable, sizeof(AccelTable) / sizeof(AccelTable[0]));

  while(GetMessage(&msg, NULL, 0, 0)) {
    if(!TranslateAccelerator(wnd_Frame, Accel, &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  return(msg.wParam);
}
