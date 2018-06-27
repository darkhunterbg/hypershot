#include "stdafx.h"

#include <stdarg.h>
#include <string>
#include <exception>

namespace debug
{
	AssertFailedCallback __onAssertFailed;

	void __AssertFail(const char* msg, const char* file, const int line, ...)
	{
		std::string dbgMessage = "Assert failed: ";

		const int bufferSize = 4096;

		char buffer[bufferSize];

		va_list args;
		va_start(args, line);
		vsnprintf_s(buffer, bufferSize, msg, args);
		va_end(args);

		dbgMessage += buffer;
		dbgMessage += " At: ";
		dbgMessage += file;
		dbgMessage += " Line: ";
		dbgMessage += std::to_string(line);
		dbgMessage += "\n";

		if (__onAssertFailed != nullptr)
			__onAssertFailed(dbgMessage);

		throw std::exception(msg);
	}
}