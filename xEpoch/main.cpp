
#include "Windows.h"
#include <cstdio>
#include <ctime>
#include <cstring>

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	char output[256];
	size_t len;
	time_t epoch;
	HGLOBAL hMem;
	char progname[256];
	char *shortname;

	time(&epoch);

	GetModuleFileName(NULL, progname, sizeof(progname));
	for (shortname = progname + strlen(progname); shortname > progname; --shortname) {
		if ('.' == *shortname) {
			*shortname = 0;
		} else if ('@' == *shortname) {
			shortname += 1;
			break;
		}
	}
	if (shortname != progname) {
		snprintf(output, sizeof(output), "%09llx-%s", epoch, shortname);
	} else {
		snprintf(output, sizeof(output), "%09llx", epoch);
	}

	len = strlen(output) + 1;

	hMem = GlobalAlloc(GMEM_MOVEABLE, len);
	memcpy(GlobalLock(hMem), output, len);
	GlobalUnlock(hMem);
	OpenClipboard(0);
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hMem);
	CloseClipboard();
}
