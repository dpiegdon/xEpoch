
#include "Windows.h"
#include <cstdio>
#include <ctime>
#include <cstring>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	char output[64];
	size_t len;
	time_t epoch;

	time(&epoch);

	snprintf(output, sizeof(output), "%llx\n", epoch);
	len = strlen(output) + 1;

	HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}

