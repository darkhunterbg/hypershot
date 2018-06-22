#pragma once


void __Assert(bool expr, const char* msg, const char* file, const int line);

#define ASSERT(Expr, Msg) __Assert(Expr,Msg,__FILE__,__LINE__);

