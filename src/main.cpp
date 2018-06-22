#include "stdafx.h"

#include<Windows.h>

#include "MemoryService.h"

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lcCmdLine, _In_ int nCmdShow)
{
	MemoryService service;
	service.Allocate(1024);

	return 0;
}