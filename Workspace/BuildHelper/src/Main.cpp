#include<iostream>

//This New Is Used Only For Debugging Purposes Set The Debugging Flag For The Event System To Use This...
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Symbols.h"
#include "Example1.h"

#include "EventBroadcastStation.h"

int main()
{
	//Start Initialize Memory Leak Checking Module..
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetDbgFlag(flag);
	//Ended Initialize Memory Leak Checking Module..


	//Start Call Which Example You Want Here//
	Example1Main();
	//Ended Call Which Example You Want Here//
	
	ErmineEventSystem::EventBroadcastStation::DestroyStation(); //:> Forgot To Destroy The Station After Use.. Previously
		
	//Start Print Detected Memory Leaks To File..
	FILE* pFile;
	freopen_s(&pFile, "MemoryLeakLog.txt", "w", stdout);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks(); fclose(pFile);
	//Ended Print Detected Memory Leaks To File..
}