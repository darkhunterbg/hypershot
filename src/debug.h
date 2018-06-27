#pragma once

#include <string>

typedef void(*AssertFailedCallback)(const std::string& msg);
typedef std::string* (*AssertParamEval)();

namespace debug
{
	extern AssertFailedCallback __onAssertFailed ;

	void __AssertFail( const char* msg, const char* file, const int line, ...);

}
#if defined( _DEBUG)
#define ASSERT(Expr, Msg,...) if(!(Expr)) debug::__AssertFail(Msg,__FILE__,__LINE__, __VA_ARGS__)

#else
#define ASSERT(Expr, Msg,...) 
#endif
