#include "stdafx.h"

#include<Windows.h>

#include "MemoryService.h"

int CALLBACK WinMain(IN HINSTANCE hInstance, IN HINSTANCE hPrevInstance, IN LPSTR lcCmdLine, IN int nCmdShow)
{
	SYSTEM_INFO sysInfo ;

	GetSystemInfo(&sysInfo);

	MemoryService service(sysInfo.dwPageSize);
	service.Allocate(1024);

	return 0;
}
