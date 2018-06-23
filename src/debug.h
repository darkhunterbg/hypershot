#pragma once


void __Assert(bool expr, const char* msg, const char* file, const int line,  ...);

#if defined( _DEBUG)
#define ASSERT(Expr, Msg,...) __Assert(Expr,Msg,__FILE__,__LINE__, __VA_ARGS__)
#else
#define ASSERT(Expr, Msg,...) 
#endif
