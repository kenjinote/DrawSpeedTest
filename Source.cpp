#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma comment(lib, "gdiplus.lib")

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HWND hButton1;
	static HWND hButton2;
	static HWND hButton3;
	static HWND hButton4;
	static HWND hEdit;
	static HFONT hFont;
	switch (msg)
	{
	case WM_CREATE:
		hFont = CreateFontW(-MulDiv(10, 96, 72), 0, 0, 0, FW_NORMAL, 0, 0, 0, SHIFTJIS_CHARSET, 0, 0, 0, 0, L"MS Shell Dlg");
		hButton1 = CreateWindow(TEXT("BUTTON"), TEXT("描画1"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1000, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton1, WM_SETFONT, (WPARAM)hFont, 0);
		hButton2 = CreateWindow(TEXT("BUTTON"), TEXT("描画2"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1001, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton2, WM_SETFONT, (WPARAM)hFont, 0);
		hButton3 = CreateWindow(TEXT("BUTTON"), TEXT("描画3"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1002, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton3, WM_SETFONT, (WPARAM)hFont, 0);
		hButton4 = CreateWindow(TEXT("BUTTON"), TEXT("描画4"), WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)1003, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hButton4, WM_SETFONT, (WPARAM)hFont, 0);
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), 0, WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_READONLY, 0, 0, 0, 0, hWnd, 0, ((LPCREATESTRUCT)lParam)->hInstance, 0);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hFont, 0);
		break;
	case WM_SIZE:
		MoveWindow(hButton1, 0, 0, 64, 32, TRUE);
		MoveWindow(hButton2, 64, 0, 64, 32, TRUE);
		MoveWindow(hButton3, 128, 0, 64, 32, TRUE);
		MoveWindow(hButton4, 192, 0, 64, 32, TRUE);
		MoveWindow(hEdit, 256, 0, LOWORD(lParam) - 256, 32, TRUE);
		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == 1000)
		{
			RECT rect;
			GetClientRect(hWnd, &rect);

			LARGE_INTEGER nFreq = { 0 }, nBefore = { 0 }, nAfter = { 0 };
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBefore);

			{
				HDC hdc = GetDC(hWnd);
				PatBlt(hdc, 0, 0, rect.right, rect.bottom, WHITENESS);
				for (int i = 0; i < rect.right / 2; ++i)
				{
					MoveToEx(hdc, i * 2, rand() % rect.bottom, 0);
					LineTo(hdc, i * 2 + 2, rand() % rect.bottom);
				}
				ReleaseDC(hWnd, hdc);
			}

			QueryPerformanceCounter(&nAfter);
			DWORD dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);

			TCHAR szText[1024];
			wsprintf(szText, TEXT("%dミリ秒"), dwTime);
			SetWindowText(hEdit, szText);
		}
		if (LOWORD(wParam) == 1001)
		{
			RECT rect;
			GetClientRect(hWnd, &rect);

			LARGE_INTEGER nFreq = { 0 }, nBefore = { 0 }, nAfter = { 0 };
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBefore);

			{
				HDC hdc = GetDC(hWnd);
				HDC hMemDC = CreateCompatibleDC(hdc);
				HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
				HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
				PatBlt(hMemDC, 0, 0, rect.right, rect.bottom, WHITENESS);
				for (int i = 0; i < rect.right / 2; ++i)
				{
					MoveToEx(hMemDC, i * 2, rand() % rect.bottom, 0);
					LineTo(hMemDC, i * 2 + 2, rand() % rect.bottom);
				}
				BitBlt(hdc, 0, 0, rect.right, rect.bottom, hMemDC, 0, 0, SRCCOPY);
				SelectObject(hMemDC, hOldBitmap);
				DeleteObject(hBitmap);
				DeleteDC(hMemDC);
				ReleaseDC(hWnd, hdc);
			}

			QueryPerformanceCounter(&nAfter);
			DWORD dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);

			TCHAR szText[1024];
			wsprintf(szText, TEXT("%dミリ秒"), dwTime);
			SetWindowText(hEdit, szText);
		}
		if (LOWORD(wParam) == 1002)
		{
			RECT rect;
			GetClientRect(hWnd, &rect);

			LARGE_INTEGER nFreq = { 0 }, nBefore = { 0 }, nAfter = { 0 };
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBefore);

			{
				ULONG_PTR gdiToken;
				GdiplusStartupInput gdiSI;
				GdiplusStartup(&gdiToken, &gdiSI, NULL);
				HDC hdc = GetDC(hWnd);
				{
					Graphics g(hdc);
					g.Clear(Color::White);
					Pen pen(Color::Black, 1.0f);
					for (int i = 0; i < rect.right / 2; ++i)
					{
						g.DrawLine(&pen, Point(i * 2, rand() % rect.bottom), Point(i * 2 + 2, rand() % rect.bottom));
					}
				}
				ReleaseDC(hWnd, hdc);
				GdiplusShutdown(gdiToken);
			}

			QueryPerformanceCounter(&nAfter);
			DWORD dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);

			TCHAR szText[1024];
			wsprintf(szText, TEXT("%dミリ秒"), dwTime);
			SetWindowText(hEdit, szText);
		}
		if (LOWORD(wParam) == 1003)
		{
			RECT rect;
			GetClientRect(hWnd, &rect);

			LARGE_INTEGER nFreq = { 0 }, nBefore = { 0 }, nAfter = { 0 };
			QueryPerformanceFrequency(&nFreq);
			QueryPerformanceCounter(&nBefore);

			{
				ULONG_PTR gdiToken;
				GdiplusStartupInput gdiSI;
				GdiplusStartup(&gdiToken, &gdiSI, NULL);
				{
					Bitmap bitmap(rect.right, rect.bottom);
					{
						Graphics g(&bitmap);
						g.Clear(Color::White);
						Pen pen(Color::Black, 1.0f);
						for (int i = 0; i < rect.right / 2; ++i)
						{
							g.DrawLine(&pen, Point(i * 2, rand() % rect.bottom), Point(i * 2 + 2, rand() % rect.bottom));
						}
					}
					{
						HDC hdc = GetDC(hWnd);
						{
							Graphics g(hdc);
							Rect r = { 0, 0, rect.right, rect.bottom };
							g.DrawImage(&bitmap, r);
						}
						ReleaseDC(hWnd, hdc);
					}
				}
				GdiplusShutdown(gdiToken);
			}

			QueryPerformanceCounter(&nAfter);
			DWORD dwTime = (DWORD)((nAfter.QuadPart - nBefore.QuadPart) * 1000 / nFreq.QuadPart);

			TCHAR szText[1024];
			wsprintf(szText, TEXT("%dミリ秒"), dwTime);
			SetWindowText(hEdit, szText);
		}

		break;
	case WM_DESTROY:
		DeleteObject(hFont);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindow(
		szClassName,
		TEXT("Window"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}
