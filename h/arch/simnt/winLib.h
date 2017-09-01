/* winLib.h - wrappers for WIN32 structures, constants & functions
 *		  required by UGL SIMNT driver */

/* Copyright 2000 Wind River Systems, Inc. */

/* 
modification history 
--------------------
01d,14nov00,msr  Added support for middle pointer button.
01c,09nov00,msr  Added routines needed for keyboard mapping.
01b,19oct00,msr  Fixed arrow keys and other special keys.
01a,22may00,lcs written
*/

/* 
DESCRIPTION
This file redefines all WIN32 functions & data structures/types required by the
SIMNT UGL driver. 
*/

#ifndef INCugl_winLibh
#define INCugl_winLibh


#define WIN_BI_RGB		(0L)
#define WIN_CBM_INIT		(0x4L)
#define WIN_DIB_RGB_COLORS	(0)

#define win_max(a, b) (((a) > (b)) ? (a) : (b))
#define win_GetRValue(rgb)   ((WIN_BYTE) (rgb)) 
#define win_GetGValue(rgb)   ((WIN_BYTE) (((WIN_WORD) (rgb)) >> 8)) 
#define win_GetBValue(rgb)   ((WIN_BYTE) ((rgb) >> 16))

typedef unsigned char	WIN_BYTE;
typedef unsigned long 	WIN_COLORREF;
typedef long		WIN_LONG;
typedef unsigned short	WIN_WORD;
typedef unsigned short  WIN_ATOM;
typedef unsigned int 	WIN_UINT;
typedef unsigned int 	WIN_WPARAM;
typedef WIN_LONG	WIN_LPARAM;

#ifndef __cplusplus
typedef unsigned short WIN_WCHAR;
#else
typedef wchar_t WIN_WCHAR;
#endif

typedef char	WIN_CHAR;
typedef short	WIN_SHORT;

typedef void *          WIN_PVOID;
typedef long		WIN_LRESULT;

typedef WIN_HANDLE	WIN_HBITMAP;
typedef WIN_HANDLE	WIN_HBRUSH;
typedef WIN_HANDLE	WIN_HCURSOR;
typedef WIN_HANDLE	WIN_HDC;
typedef WIN_HANDLE	WIN_HGDIOBJ;
typedef WIN_HANDLE	WIN_HICON;
typedef WIN_HANDLE	WIN_HINSTANCE;
typedef WIN_HANDLE	WIN_HMENU;
typedef WIN_HANDLE	WIN_HPEN;
typedef WIN_HANDLE	WIN_HRGN;
typedef WIN_HANDLE	WIN_HWND;

typedef unsigned char 	WIN_UCHAR;
typedef unsigned long 	WIN_ULONG;
typedef unsigned short 	WIN_USHORT;

typedef const char *	WIN_LPCSTR;
typedef const WIN_WCHAR *WIN_LPCWSTR;

/* Only use __stdcall under WIN32 compiler */
#ifdef i386
#define STDCALL     __attribute__ ((stdcall))
#define CDECL       __cdecl
#define PASCAL      WINAPI
#else
#define STDCALL
#define CDECL
#define PASCAL
#endif
#define WINAPI      STDCALL
#define APIENTRY    STDCALL
#define WINGDIAPI


#ifdef UNICODE
typedef const unsigned short *WIN_LPCTSTR;
typedef unsigned short *WIN_LPTSTR;

#define win_CreateWindow  win_CreateWindowW
#define win_CreateWindowW(lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
win_CreateWindowExW(0L, lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)

#else
typedef const char *WIN_LPCTSTR;
typedef char *WIN_LPTSTR;

#define win_CreateWindow  win_CreateWindowA
#define win_CreateWindowA(lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)\
win_CreateWindowExA(0L, lpClassName, lpWindowName, dwStyle, x, y,\
nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam)

#endif

typedef int WIN_CALLBACK (*WIN_BFFCALLBACK) 
	(WIN_HWND, WIN_UINT, WIN_LPARAM, WIN_LPARAM);
typedef WIN_UINT WIN_CALLBACK (*WIN_LPCCHOOKPROC) 
	(WIN_HWND, WIN_UINT, WIN_WPARAM, WIN_LPARAM);
typedef WIN_UINT WIN_CALLBACK (*WIN_LPCFHOOKPROC) 
	(WIN_HWND, WIN_UINT, WIN_WPARAM, WIN_LPARAM);
typedef WIN_LRESULT WIN_CALLBACK (*WIN_WNDPROC) 
	(WIN_HWND, WIN_UINT, WIN_WPARAM, WIN_LPARAM);

typedef struct _WIN_WNDCLASSA {
    WIN_UINT    style;
    WIN_WNDPROC lpfnWndProc;
    int     cbClsExtra;
    int     cbWndExtra;
    WIN_HANDLE  hInstance;
    WIN_HICON   hIcon;
    WIN_HCURSOR hCursor;
    WIN_HBRUSH  hbrBackground;
    WIN_LPCSTR  lpszMenuName;
    WIN_LPCSTR  lpszClassName;
} WIN_WNDCLASSA, *WIN_LPWNDCLASSA;

typedef struct _WIN_WNDCLASSEXW {
  WIN_UINT	cbSize;
  WIN_UINT	style;
  WIN_WNDPROC	lpfnWndProc;
  int		cbClsExtra;
  int		cbWndExtra;
  WIN_HANDLE	hInstance;
  WIN_HICON	hIcon;
  WIN_HCURSOR	hCursor;
  WIN_HBRUSH	hbrBackground;
  WIN_LPCWSTR	lpszMenuName;
  WIN_LPCWSTR	lpszClassName;
  WIN_HICON	hIconSm;
} WIN_WNDCLASSEXW, *WIN_LPWNDCLASSEXW;

#ifdef UNICODE
typedef WIN_WNDCLASSW       WIN_WNDCLASS;
#else
typedef WIN_WNDCLASSA       WIN_WNDCLASS;
#endif
typedef WIN_WNDCLASS        *WIN_LPWNDCLASS;

typedef struct WIN_tagRGBQUAD {
    WIN_BYTE    rgbBlue;
    WIN_BYTE    rgbGreen;
    WIN_BYTE    rgbRed;
    WIN_BYTE    rgbReserved;
} WIN_RGBQUAD;

typedef struct WIN_tagBITMAPINFOHEADER {
    WIN_DWORD  biSize;
    WIN_LONG   biWidth;
    WIN_LONG   biHeight;
    WIN_WORD   biPlanes;
    WIN_WORD   biBitCount;
    WIN_DWORD  biCompression;
    WIN_DWORD  biSizeImage;
    WIN_LONG   biXPelsPerMeter;
    WIN_LONG   biYPelsPerMeter;
    WIN_DWORD  biClrUsed;
    WIN_DWORD  biClrImportant;
} WIN_BITMAPINFOHEADER, *WIN_LPBITMAPINFOHEADER, *WIN_PBITMAPINFOHEADER;

typedef struct WIN_tagBITMAPINFO {
    WIN_BITMAPINFOHEADER bmiHeader;
    WIN_RGBQUAD          bmiColors[1];
} WIN_BITMAPINFO, *WIN_LPBITMAPINFO, *WIN_PBITMAPINFO;
    
typedef struct WIN_tagPOINT {
    WIN_LONG x;
    WIN_LONG y;
} WIN_POINT, *WIN_LPPOINT, *WIN_PPOINT;

typedef struct _WIN_RECT {
	WIN_LONG left;
	WIN_LONG top;
	WIN_LONG right;
	WIN_LONG bottom;
} WIN_RECT, *WIN_LPRECT, *WIN_PRECT;
	
typedef struct WIN_tagMSG {
    WIN_HWND   hwnd;
    WIN_UINT   message;
    WIN_WPARAM wParam;
    WIN_LPARAM lParam;
    WIN_DWORD  time;
    WIN_POINT  pt;
} WIN_MSG, *WIN_LPMSG;

typedef struct WIN_tagPAINTSTRUCT {
    WIN_HDC  hdc;
    WIN_BOOL fErase;
    WIN_RECT rcPaint;
    WIN_BOOL fRestore;
    WIN_BOOL fIncUpdate;
    WIN_BYTE rgbReserved[32];
} WIN_PAINTSTRUCT, *WIN_LPPAINTSTRUCT;


typedef struct WIN_tagLIST_ENTRY { 
  struct WIN_tagLIST_ENTRY *Flink; 
  struct WIN_tagLIST_ENTRY *Blink; 
} WIN_LIST_ENTRY, *WIN_PLIST_ENTRY; 
 
typedef struct WIN_tagCRITICAL_SECTION_DEBUG {
    WIN_WORD   Type;
    WIN_WORD   CreatorBackTraceIndex;
    struct WIN_tagCRITICAL_SECTION *CriticalSection;
    WIN_LIST_ENTRY ProcessLocksList;
    WIN_DWORD EntryCount;
    WIN_DWORD ContentionCount;
    WIN_DWORD Depth;
    WIN_PVOID OwnerBackTrace[ 5 ];
} WIN_CRITICAL_SECTION_DEBUG, *WIN_PCRITICAL_SECTION_DEBUG;

typedef struct WIN_tagCRITICAL_SECTION {
    WIN_PCRITICAL_SECTION_DEBUG DebugInfo;
    WIN_LONG LockCount;
    WIN_LONG RecursionCount;
    WIN_HANDLE OwningThread;
    WIN_HANDLE LockSemaphore;
    WIN_DWORD Reserved;
} WIN_CRITICAL_SECTION, *WIN_PCRITICAL_SECTION, *WIN_LPCRITICAL_SECTION;


#define WIN_RGB(r, g ,b) ((WIN_DWORD) (((WIN_BYTE) (r) | \
    ((WIN_WORD) (g) << 8)) | \
    (((WIN_DWORD) (WIN_BYTE) (b)) << 16))) 

#define WIN_MAKEINTRESOURCE(i)  (WIN_LPTSTR) ((WIN_DWORD) ((WIN_WORD) (i)))

#define WIN_LOWORD(l)   ((WIN_WORD) (l))
#define WIN_HIWORD(l)   ((WIN_WORD) (((WIN_DWORD) (l) >> 16) & 0xFFFF)) 

/* GetIconInfo */
#define WIN_IDC_ARROW       (WIN_MAKEINTRESOURCE(32512))
#define WIN_IDC_IBEAM       (WIN_MAKEINTRESOURCE(32513))
#define WIN_IDC_WAIT        (WIN_MAKEINTRESOURCE(32514))
#define WIN_IDC_CROSS       (WIN_MAKEINTRESOURCE(32515))
#define WIN_IDC_UPARROW     (WIN_MAKEINTRESOURCE(32516))
#define WIN_IDC_SIZENWSE    (WIN_MAKEINTRESOURCE(32642))
#define WIN_IDC_SIZENESW    (WIN_MAKEINTRESOURCE(32643))
#define WIN_IDC_SIZEWE      (WIN_MAKEINTRESOURCE(32644))
#define WIN_IDC_SIZENS      (WIN_MAKEINTRESOURCE(32645))
#define WIN_IDC_SIZEALL     (WIN_MAKEINTRESOURCE(32646))
#define WIN_IDC_NO  (WIN_MAKEINTRESOURCE(32648))
#define WIN_IDC_APPSTARTING (WIN_MAKEINTRESOURCE(32650))
#define WIN_IDC_HELP        (WIN_MAKEINTRESOURCE(32651))
#define WIN_IDI_APPLICATION (WIN_MAKEINTRESOURCE(32512))
#define WIN_IDI_HAND        (WIN_MAKEINTRESOURCE(32513))
#define WIN_IDI_QUESTION    (WIN_MAKEINTRESOURCE(32514))
#define WIN_IDI_EXCLAMATION (WIN_MAKEINTRESOURCE(32515))
#define WIN_IDI_ASTERISK    (WIN_MAKEINTRESOURCE(32516))
#define WIN_IDI_WINLOGO     (WIN_MAKEINTRESOURCE(32517))
#define WIN_IDC_SIZE        (WIN_MAKEINTRESOURCE(32640))
#define WIN_IDC_ICON        (WIN_MAKEINTRESOURCE(32641))


/* WNDCLASS structure */
#define WIN_CS_BYTEALIGNCLIENT      (4096)
#define WIN_CS_BYTEALIGNWINDOW      (8192)
#define WIN_CS_CLASSDC      (64)
#define WIN_CS_DBLCLKS      (8)
#define WIN_CS_GLOBALCLASS  (16384)
#define WIN_CS_HREDRAW      (2)
#define WIN_CS_KEYCVTWINDOW (4)
#define WIN_CS_NOCLOSE      (512)
#define WIN_CS_NOKEYCVT     (256)
#define WIN_CS_OWNDC        (32)
#define WIN_CS_PARENTDC     (128)
#define WIN_CS_SAVEBITS     (2048)
#define WIN_CS_VREDRAW      (1)
#define WIN_DLGWINDOWEXTRA  (30)

/* SetWindowPos, DeferWindowPos */
#define WIN_SWP_NOACTIVATE  (16)
#define WIN_SWP_NOMOVE      (2)
#define WIN_SWP_NOZORDER    (4)

/* Ternary Raster Operations - BitBlt */
#define WIN_SRCINVERT       0x00660046
#define WIN_SRCAND  0x008800C6
#define WIN_SRCCOPY 0x00CC0020
#define WIN_SRCPAINT        0x00EE0086

/* Binary Raster Operations */
#define WIN_R2_COPYPEN	(13)
#define WIN_R2_MASKPEN	(9)
#define WIN_R2_MERGEPEN	(15)
#define WIN_R2_XORPEN	(7)

/* ShowWindow */
#define WIN_SW_SHOWNORMAL (1)
#define WIN_SW_SHOW (5)

/* CombineRgn */
#define WIN_RGN_OR  (2)

/* CreatePen, ExtCreatePen */
#define WIN_PS_SOLID	(0)
#define WIN_PS_NULL 	(5)

/* GetStockObject */
#define WIN_NULL_BRUSH      (5)

/* thread priorities */

#define WIN_THREAD_PRIORITY_NORMAL	(0)
#define WIN_THREAD_PRIORITY_HIGHEST	(2)

/* Virtual Key codes */
#define WIN_VK_CAPITAL		(20)
#define WIN_VK_NUMLOCK		(144)
#define WIN_VK_SCROLL		(145)
#define WIN_VK_SHIFT	        (16)
#define WIN_VK_CONTROL          (17)
#define WIN_VK_MENU             (18)
#define WIN_VK_LSHIFT		(160)
#define WIN_VK_RSHIFT		(161)
#define WIN_VK_LCONTROL		(162)
#define WIN_VK_RCONTROL		(163)
#define WIN_VK_LMENU		(164)
#define WIN_VK_RMENU		(165)
#define WIN_VK_F1	        (112)
#define WIN_VK_F2	        (113)
#define WIN_VK_F3	        (114)
#define WIN_VK_F4	        (115)
#define WIN_VK_F5	        (116)
#define WIN_VK_F6	        (117)
#define WIN_VK_F7	        (118)
#define WIN_VK_F8	        (119)
#define WIN_VK_F9	        (120)
#define WIN_VK_F10	        (121)
#define WIN_VK_F11	        (122)
#define WIN_VK_F12	        (123)
#define WIN_VK_LEFT	        (37)
#define WIN_VK_RIGHT	        (39)
#define WIN_VK_UP	        (38)
#define WIN_VK_DOWN	        (40)
#define WIN_VK_HOME	        (36)
#define WIN_VK_END	        (35)
#define WIN_VK_INSERT	        (45)
#define WIN_VK_DELETE	        (46)
#define WIN_VK_PRIOR	        (33)
#define WIN_VK_NEXT	        (34)
#define WIN_VK_ESCAPE	        (27)

#define WIN_WM_CLOSE		(16)
#define WIN_WM_KEYDOWN		(256)
#define WIN_WM_KEYUP		(257)
#define WIN_WM_CHAR             (258)
#define WIN_WM_SYSKEYDOWN       (260)
#define WIN_WM_SYSKEYUP         (261)
#define WIN_WM_SYSCHAR          (262)
#define WIN_WM_LBUTTONDOWN	(513)
#define WIN_WM_LBUTTONUP	(514)
#define WIN_WM_RBUTTONDOWN      (516)
#define WIN_WM_RBUTTONUP        (517)
#define WIN_WM_MBUTTONDOWN      (519)
#define WIN_WM_MBUTTONUP        (520)
#define WIN_WM_MOUSEMOVE	(512)
#define WIN_WM_PAINT		(15)
#define WIN_WM_SETCURSOR	(32)
#define WIN_WM_QUIT 		(18)

#define WIN_WS_CAPTION		(0xc00000L)
#define WIN_WS_MINIMIZEBOX	(0x20000L)
#define WIN_WS_OVERLAPPED	(0L)
#define WIN_WS_SYSMENU		(0x80000L)

#define WIN_GWL_USERDATA	(-6)
#define WIN_GWL_HINSTANCE	(-21)

#define WIN_HTCLIENT		(1)

/* Mouse messages */
#define WIN_MK_LBUTTON	(1)
#define WIN_MK_MBUTTON	(16)
#define WIN_MK_RBUTTON	(2)

#ifdef __STDC__
WIN_BOOL win_Arc (WIN_HDC hdc, int arg0, int arg1, int arg2, int arg3,
		  int arg4, int arg5, int arg6, int arg7);
WIN_HDC win_BeginPaint (WIN_HWND hWnd, WIN_LPPAINTSTRUCT lpPaint);
WIN_BOOL win_BitBlt (WIN_HDC hdc1, int arg0, int arg1, int arg2, int arg3,
		     WIN_HDC hdc2, int arg4, int arg5, WIN_DWORD dwd);
int win_CombineRgn (WIN_HRGN rgn0, WIN_HRGN rgn1, WIN_HRGN rgn2, int arg0);
WIN_HBITMAP win_CreateCompatibleBitmap (WIN_HDC hdc, int arg0, int arg1);
WIN_HDC win_CreateCompatibleDC (WIN_HDC hdc);
WIN_HBITMAP win_CreateBitmap (int arg0, int arg1, WIN_UINT uint0, 
			      WIN_UINT uint1, const void * pVoid);
WIN_HDC win_CreateDIBitmap (WIN_HDC hdc, 
			    const WIN_BITMAPINFOHEADER * pBmpInfoHdr,
			    WIN_DWORD dwd, const void * pVoid, 
			    const WIN_BITMAPINFO * pBmpInfo, WIN_UINT arg);
WIN_HPEN win_CreatePen (int arg0, int arg1, WIN_COLORREF clrRef);
WIN_HRGN win_CreateRectRgn (int arg0, int arg1, int arg2, int arg3);
WIN_HBRUSH win_CreateSolidBrush (WIN_COLORREF colorRef);
WIN_HANDLE win_CreateThread (WIN_LPSECURITY_ATTRIBUTES lpThreadAttributes, 
                             WIN_DWORD stack, WIN_LPTHREAD_START_ROUTINE start, 
                             WIN_LPVOID param, WIN_DWORD flags,
                             WIN_LPDWORD threadId);
WIN_HWND win_CreateWindowExA (WIN_DWORD dwExStyle, WIN_LPCSTR lpClassName, 
			      WIN_LPCSTR lpWindowName,
			      WIN_DWORD dwStyle, int X, int Y, int nWidth,
			      int nHeight, WIN_HWND hWndParent, WIN_HMENU hMenu,
			      WIN_HINSTANCE hInstance, WIN_LPVOID lpParam);
WIN_HWND win_CreateWindowExW (WIN_DWORD dwExStyle, WIN_LPCWSTR lpClassName, 
			      WIN_LPCWSTR lpWindowName,
			      WIN_DWORD dwStyle, int X, int Y, int nWidth,
			      int nHeight, WIN_HWND hWndParent, WIN_HMENU hMenu,
			      WIN_HINSTANCE hInstance, WIN_LPVOID lpParam);
WIN_LRESULT win_DefWindowProc (WIN_HWND hWnd, WIN_UINT msg, WIN_WPARAM wParam,
			       WIN_LPARAM lParam);
WIN_BOOL win_DeleteDC (WIN_HDC hdc);
WIN_BOOL win_DeleteObject (WIN_HGDIOBJ hgdiobj);
WIN_BOOL win_DestroyWindow (WIN_HWND hWnd);
WIN_LONG win_DispatchMessage (const WIN_MSG * lpMsg);
WIN_BOOL win_Ellipse (WIN_HDC hdc, int arg0, int arg1, int arg2, int arg3);
WIN_BOOL win_EndPaint (WIN_HWND hWnd, const WIN_PAINTSTRUCT * lpPaint);
int win_FillRect (WIN_HDC hdc, const WIN_RECT * lprc, WIN_HBRUSH hbr);
WIN_HWND win_FindWindow (WIN_LPCTSTR lpClassName, WIN_LPCTSTR lpWindowName);
WIN_BOOL win_GetClientRect (WIN_HWND hWnd, WIN_LPRECT lpRect);
WIN_HDC win_GetDC (WIN_HWND hWnd);
WIN_SHORT win_GetKeyState(int nVirtKey);
WIN_COLORREF win_GetPixel (WIN_HDC hdc, int arg0, int arg1);
WIN_BOOL win_GetMessage (WIN_LPMSG lpMsg, WIN_HWND hWnd, WIN_UINT wMsgFilterMin,
			 WIN_UINT wMsgFilterMax);
WIN_LONG win_GetWindowLong (WIN_HWND hWnd, int nIndex);
WIN_HGDIOBJ win_GetStockObject (int arg0);
WIN_BOOL win_LineTo (WIN_HDC hdc, int arg0, int arg1);
WIN_HICON win_LoadIcon (WIN_HINSTANCE hInstance, WIN_LPCSTR lpIconName);
WIN_UINT win_MapVirtualKey (WIN_UINT uCode, WIN_UINT uMapType);
WIN_BOOL win_MoveToEx (WIN_HDC hdc, int arg0, int arg1, WIN_LPPOINT pt);
WIN_BOOL win_Pie (WIN_HDC hdc, int arg0, int arg1, int arg2, int arg3,
		  int arg4, int arg5, int arg6, int arg7);
WIN_BOOL win_Polygon (WIN_HDC hdc, const WIN_POINT * pt, int arg);
WIN_BOOL win_PostMessage (WIN_HWND hWnd, WIN_UINT msg, WIN_WPARAM wParam,
			  WIN_LPARAM lParam);
WIN_BOOL win_Rectangle (WIN_HDC hDC, int arg0, int arg1, int arg2, int arg3); 
WIN_ATOM win_RegisterClass (const WIN_WNDCLASS * lpWndClass);
int win_ReleaseDC (WIN_HWND hWnd, WIN_HDC hDC);
int win_SelectClipRgn (WIN_HDC hDC, WIN_HRGN hRgn);
WIN_HGDIOBJ win_SelectObject (WIN_HDC hdc, WIN_HGDIOBJ obj);
WIN_COLORREF win_SetBkColor (WIN_HDC hdc, WIN_COLORREF colorRef);
WIN_HCURSOR win_SetCursor (WIN_HCURSOR hCursor);
WIN_BOOL win_SetForegroundWindow(WIN_HWND hWnd);
WIN_COLORREF win_SetPixel (WIN_HDC hdc, int arg1, int arg2, 
			   WIN_COLORREF colorRef);
int win_SetROP2(WIN_HDC hdc, int fnDrawMode);
WIN_COLORREF win_SetTextColor (WIN_HDC hdc, WIN_COLORREF colorRef);
WIN_BOOL win_SetThreadPriority(WIN_HANDLE hThread, int nPriority);
WIN_LONG win_SetWindowLong (WIN_HWND hWnd, int nIndex, WIN_LONG dwNewLong);
WIN_BOOL win_SetWindowPos (WIN_HWND hWnd, WIN_HWND hWndInsertAfter, int X,
			   int Y, int cx, int cy, WIN_UINT uFlags);
WIN_BOOL win_ShowWindow (WIN_HWND hWnd, int nCmdShow);
void win_Sleep (WIN_DWORD dwMilliseconds);
WIN_BOOL win_StretchBlt (WIN_HDC hdc1, int arg0, int arg1, int arg2, int arg3,
			 WIN_HDC hdc2, int arg4, int arg5, int arg6, int arg7,
			 WIN_DWORD dwd);
WIN_BOOL win_TranslateMessage (const WIN_MSG *lpMsg);
void win_InitializeCriticalSection (WIN_LPCRITICAL_SECTION lpCriticalSection);
void win_EnterCriticalSection (WIN_LPCRITICAL_SECTION lpCriticalSection);
void win_LeaveCriticalSection (WIN_LPCRITICAL_SECTION lpCriticalSection);
void win_DeleteCriticalSection (WIN_LPCRITICAL_SECTION lpCriticalSection);

#else
WIN_BOOL win_Arc ();
WIN_HDC win_BeginPaint ();
WIN_BOOL win_BitBlt ();
int win_CombineRgn ();
WIN_HBITMAP win_CreateCompatibleBitmap ();
WIN_HDC win_CreateCompatibleDC ();
WIN_HBITMAP win_CreateBitmap ();
WIN_HDC win_CreateDIBitmap ();
WIN_HPEN win_CreatePen ();
WIN_HRGN win_CreateRectRgn ();
WIN_HBRUSH win_CreateSolidBrush ();
WIN_HANDLE win_CreateThread ();
WIN_HWND win_CreateWindowExA ();
WIN_HWND win_CreateWindowExW ();
WIN_LRESULT win_DefWindowProc ();
WIN_BOOL win_DeleteDC ();
WIN_BOOL win_DeleteObject ();
WIN_BOOL win_DestroyWindow ();
WIN_LONG win_DispatchMessage ();
WIN_BOOL win_Ellipse ();
WIN_BOOL win_EndPaint ();
int win_FillRect ();
WIN_HWND win_FindWindow ();
WIN_BOOL win_GetClientRect ();
WIN_HDC win_GetDC ();
WIN_SHORT win_GetKeyState();
WIN_COLORREF win_GetPixel ();
WIN_BOOL win_GetMessage ();
WIN_LONG win_GetWindowLong ();
WIN_HGDIOBJ win_GetStockObject ();
WIN_BOOL win_LineTo ();
WIN_HICON win_LoadIcon ();
WIN_UINT win_MapVirtualKey ();
WIN_BOOL win_MoveToEx ();
WIN_BOOL win_Pie ();
WIN_BOOL win_Polygon ();
WIN_BOOL win_PostMessage ();
WIN_BOOL win_Rectangle (); 
WIN_ATOM win_RegisterClass ();
int win_ReleaseDC ();
int win_SelectClipRgn ();
WIN_HGDIOBJ win_SelectObject ();
WIN_COLORREF win_SetBkColor ();
WIN_HCURSOR win_SetCursor ();
WIN_BOOL win_SetForegroundWindow();
WIN_COLORREF win_SetPixel ();
int win_SetROP2();
WIN_COLORREF win_SetTextColor ();
WIN_BOOL win_SetThreadPriority();
WIN_LONG win_SetWindowLong ();
WIN_BOOL win_SetWindowPos ();
WIN_BOOL win_ShowWindow ();
void win_Sleep ();
WIN_BOOL win_StretchBlt ();
WIN_BOOL win_TranslateMessage (CONST MSG *lpMsg);
void win_InitializeCriticalSection ();
void win_EnterCriticalSection ();
void win_LeaveCriticalSection ();
void win_DeleteCriticalSection ();
#endif /* __STDC__ */

/* used to create linker dependancy on ugl_winLib.o */

void uglWinLibInit (void);

#endif

