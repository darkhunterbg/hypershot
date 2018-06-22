#pragma once


#ifdef _GAME
#define HSAPI __declspec(dllexport)
#else
#define HSAPI __declspec(dllimport)
#endif