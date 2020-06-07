#include <iostream>

_declspec(dllexport) void Test()
{
	std::cout << "This Works" << std::endl;
}