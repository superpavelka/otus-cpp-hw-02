#include <iostream>
#include <map>
#include <memory>

#include "MyAllocator.h"

using namespace std;

int main(int, char *[]) 
{
    
	auto m = std::map<int, int,	std::less<int>,	MyAllocator<std::pair<const int, int>>>{};
	
    return 0;
}