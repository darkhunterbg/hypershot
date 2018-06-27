#include "stdafx.h"
#include "win32.h"

std::string GetLastErrorString()
{
	DWORD error = GetLastError();
	if (error == 0)
		return std::string();

	const int messageBufferSize = 1024;

	char messageBuffer[messageBufferSize];

	size_t size = FormatMessageA( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, messageBufferSize, nullptr);

	std::string message(messageBuffer, size);

	return message;
}