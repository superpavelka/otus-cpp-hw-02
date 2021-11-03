#include <iostream>
#include <map>
#include <memory>

#include "MyAllocator.h"

using namespace std;

int main(int, char *[]) 
{
	auto s = sizeof(int);
	auto v = std::vector<int, MyAllocator<int>>{};
	v.push_back(1);
	auto m = std::map<int, float, std::less<int>, MyAllocator<std::pair<const int, float>>>{};
	//bool tr = std::is_trivially_copyable<std::map<int, float, std::less<int>, MyAllocator<std::pair<const int, float>>>>::value;
	m[0] = 1;
	for (int i = 1; i < 10; ++i) 
	{
		m[i] = m[i - 1] * 2;
	}
    return 0;
}