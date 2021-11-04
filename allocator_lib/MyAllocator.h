#pragma once

#include <iostream>
#include <memory>
#include <vector>

template <typename T, size_t total_size = 10>
struct MyAllocator {
	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;

	template <typename U> struct rebind {
		typedef MyAllocator<U> other;
	};

	MyAllocator() noexcept;
	MyAllocator(const MyAllocator& myAllocator) noexcept;
	MyAllocator(MyAllocator&& myAllocator) noexcept;
	template <class U> MyAllocator(const MyAllocator<U>& myAllocator) noexcept;

	~MyAllocator() noexcept;

	T* allocate(std::size_t size);
	void deallocate(T* p, std::size_t size);

private:
	T* p_start = nullptr;
	size_t offset = 0;
	//size_t total_size = 10;
};

template <typename T, size_t total_size>
MyAllocator<T, total_size>::MyAllocator() noexcept
{
	std::cout << "Constructor of MyAllocator T" << std::endl;
}

template <typename T, size_t total_size>
MyAllocator<T, total_size>::MyAllocator(const MyAllocator& myAllocator) noexcept : MyAllocator() {}

template <typename T, size_t total_size>
MyAllocator<T, total_size>::MyAllocator(MyAllocator&& myAllocator) noexcept
{

}

template <typename T, size_t total_size>
MyAllocator<T, total_size>::~MyAllocator() noexcept
{
	std::cout << "Destructor of MyAllocator T" << std::endl;
}

template <typename T, size_t total_size> template<class U>
MyAllocator<T, total_size>::MyAllocator(const MyAllocator<U>& myAllocator) noexcept : MyAllocator() {}

template <typename T, size_t total_size>
T* MyAllocator<T, total_size>::allocate(std::size_t count)
{
	if (!p_start)
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

template <typename T, size_t total_size>
void MyAllocator<T, total_size>::deallocate(T* p, std::size_t)
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