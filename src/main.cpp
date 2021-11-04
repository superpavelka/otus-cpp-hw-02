#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "MyAllocator.h"

using namespace std;

using standart_map = std::map<int, int>;

using map_alloc = std::map<int, int, std::less<int>, MyAllocator <std::pair<const int, int> >>;

const size_t total_size = 10;

int factorial(size_t i) 
{
	return (i <= 1) ? 1 : i * factorial(i - 1);
}

template <typename T>
auto print_map(const T& m) 
{
	for (const auto& p : m) 
	{
		std::cout << p.first << ": " << p.second << std::endl;
	}
}

int main(int, char *[]) 
{
	auto s = sizeof(int);
	auto v = std::vector<int, MyAllocator<int>>{};
	v.push_back(1);
	standart_map m;
	map_alloc ma;
	for (std::size_t i = 0; i < total_size; ++i)
	{
		m.emplace(std::make_pair(i, factorial(i)));
		ma.emplace(std::make_pair(i, factorial(i)));
	}
	print_map(m);
	print_map(ma);
    return 0;
}