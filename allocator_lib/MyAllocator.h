#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Chunk {
public:
	Chunk(std::size_t len) : total_size(len) {};
	~Chunk();

	void* node = nullptr;
	Chunk* next = nullptr;
	Chunk* prev = nullptr;
	size_t total_size;
};

Chunk::~Chunk()
{
	free(node);
	node = nullptr;
};

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

	T* allocate(std::size_t size);
	void deallocate(T* p, std::size_t size);

private:
	Chunk* mem_chunk = nullptr;
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
MyAllocator<T>::MyAllocator(const MyAllocator<U>&)
{
	// should we make a copy of the rhs.m_buffer ?
	// No, we should not!
	std::cout << "Constructor of MyAllocator T U" << std::endl;
}

template <typename T>
T* MyAllocator<T>::allocate(std::size_t count)
{
	if (!mem_chunk)
	{
		mem_chunk = new Chunk(total_size);
		mem_chunk->node = malloc(total_size * sizeof(T));
	}
	if (!mem_chunk->node)
		throw std::bad_alloc();

	if (offset + count > total_size)
	{
		mem_chunk->next = new Chunk(total_size + total_size * 2);
		mem_chunk->next->prev = mem_chunk;
		mem_chunk = mem_chunk->next;
		total_size = total_size + total_size * 2;
		mem_chunk->node = malloc(total_size * sizeof(T));
		offset = 0;
	}

	T* currentAddress = (T*)mem_chunk->node + offset;
	offset += count;

	return reinterpret_cast<T*>(currentAddress);
}

template<class T> MyAllocator<T>::~MyAllocator()
{
	std::cout << "Destructor of Allocator" << std::endl;
}

template <typename T>
void MyAllocator<T>::deallocate(T* p, std::size_t)
{
	if (mem_chunk)
	{
		while (mem_chunk->prev != nullptr)
		{
			mem_chunk = mem_chunk->prev;
			delete mem_chunk->next;
			mem_chunk->next = nullptr;
		}
		delete mem_chunk;
		mem_chunk = nullptr;
	}
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