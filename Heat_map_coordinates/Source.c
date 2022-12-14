#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>

LRESULT CALLBACK LogMouse(int iCode, WPARAM wParam, LPARAM lParam);
VOID WriteToFile(char* wstr);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
	HHOOK hHook = SetWindowsHookExW(WH_MOUSE_LL, LogMouse, NULL, NULL);
	MSG msg = { 0 };
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	UnhookWindowsHookEx(hHook);
	return 0;
}

LRESULT CALLBACK LogMouse(int iCode, WPARAM wParam, LPARAM lParam)
{
	if (wParam == 513)
	{
		long x = 0;
		long y = 0;
		MSLLHOOKSTRUCT* mouseInfo = (MSLLHOOKSTRUCT*)lParam;
		x = mouseInfo->pt.x;
		y = mouseInfo->pt.y;
		LPWSTR* str = (LPWSTR)calloc(500, sizeof(LPWSTR));
		swprintf(str, 500, L"%d;%d\n", x, y);
		WriteToFile(str);
		free(str);
	}
	return CallNextHookEx(NULL, iCode, wParam, lParam);
}

VOID WriteToFile(LPWSTR wstr)
{
	FILE* f = NULL;
	if (!_wfopen_s(&f, L"..\\CoordinatesClickMouse.txt", L"ab"))
	{
		fwrite(wstr, sizeof(WCHAR), wcslen(wstr), f);
		fclose(f);
	}
}