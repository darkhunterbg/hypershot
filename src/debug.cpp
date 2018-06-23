#include "stdafx.h"

#include <windows.h>
#include <string>
#include <exception>

void __Assert(bool expr, const char* msg, const char* file, const int line, ...)
{
	if (!expr)
	{

		std::string dbgMessage = "Assert failed: '";

		char buffer[4096];

		va_list args;
		va_start(args, msg);
		vsnprintf_s(buffer, 4096, msg, args);
		va_end(args);

		dbgMessage += buffer;
		dbgMessage += "' At: ";
		dbgMessage += file;
		dbgMessage += " Line: ";
		dbgMessage += std::to_string(line);
		dbgMessage += "\n";

		OutputDebugStringA(dbgMessage.c_str());


		throw std::exception(msg);
	}
}