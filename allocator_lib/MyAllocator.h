#pragma once

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
struct MyAllocator {
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	MyAllocator();
	~MyAllocator();
	template<typename U>
	struct rebind {
		using other = MyAllocator<U>;
	};
	
	template <typename U>
	MyAllocator(const MyAllocator<U>&);

	T* allocate (std::size_t size);	
	void deallocate (T* p, std::size_t size);

private:
	T* p_start = nullptr;
	size_t offset = 0;
	size_t total_size = 10;
};

template <typename T>
MyAllocator<T>::MyAllocator() 
{
	std::cout << "Constructor of MyAllocator" << std::endl;	
}

template <typename T>
template <typename U>
MyAllocator<T>::MyAllocator(const MyAllocator<U>& ) 
{
	// should we make a copy of the rhs.m_buffer ?
	// No, we should not!
	std::cout << "Constructor of MyAllocator T U" << std::endl;
}

template <typename T>
T* MyAllocator<T>::allocate(std::size_t count)
{
	if(!p_start)
		p_start = (T*)malloc(total_size * sizeof(T));
	if (!p_start)
		throw std::bad_alloc();	

	if (offset + count > total_size) 
	{
		throw std::bad_alloc();
	}

	T* currentAddress = p_start + offset;
	offset += count;

	return reinterpret_cast<T*>(currentAddress);
}

template<class T> MyAllocator<T>::~MyAllocator() 
{
	std::cout << "Destructor of Allocator" << std::endl;
}

template <typename T>
void MyAllocator<T>::deallocate (T* p, std::size_t ) 
{
	free(p_start);
	p_start = nullptr;
}

template <class T, class U>
constexpr bool operator== (const MyAllocator<T>&, const MyAllocator<U>&) noexcept 
{
	return false;
}

template <class T, class U>
constexpr bool operator!= (const MyAllocator<T>&, const MyAllocator<U>&) noexcept 
{
	return false;
}