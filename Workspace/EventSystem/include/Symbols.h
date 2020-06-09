#pragma once
#include<iostream>

#if defined(USINGErmineEventSystem)
	#define DLL _declspec(dllimport)
#else
	#define DLL _declspec(dllexport)
#endif

//This New Is Used Only For Debugging Purposes Set The Debugging Flag For The Event System To Use This...
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#if defined(ER_DEBUG_DEVELOP) || defined(ER_DEBUG_SHIP)
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif

#define LogBuffer(x) std::cout<<x<<std::endl;