#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "MyAllocator.h"
#include "MyList.h"

using namespace std;

using standart_map = std::map<int, int>;
using map_alloc = std::map<int, int, std::less<int>, MyAllocator <std::pair<const int, int> >>;
using list = MyList<int>;
using list_alloc = MyList<int, MyAllocator<int>>;

const size_t total_size = 10;

size_t factorial(size_t i) 
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

template <typename T, typename U = std::allocator<Node<T>>>
auto print_list(const MyList<T, U>& l) {
	auto pos = l.Head();
	while (pos) {
		std::cout << pos->value << std::endl;
		pos = pos->next;
	}
}

int main(int, char *[]) 
{
	//auto v = std::vector<int, MyAllocator<int>>{};
	//v.push_back(1);
	standart_map m;
	map_alloc ma;
	list my_list;
	list_alloc	my_list_alloc;

	for (std::size_t i = 0; i < total_size; ++i)
	{
		m.emplace(std::make_pair(i, factorial(i)));
		ma.emplace(std::make_pair(i, factorial(i)));
	}

	for (size_t i = 0; i < total_size; ++i)
	{
		my_list.push_back((factorial(i)));
		my_list_alloc.push_back((factorial(i)));
	}

	print_map(m);
	print_map(ma);

	print_list(my_list);
	print_list(my_list_alloc);

    return 0;
}