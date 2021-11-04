#pragma once

#include <iostream>
#include <memory>

class Chunk {
public:
	Chunk(std::size_t len) : total_size(len) {};
	~Chunk();

	void* node = nullptr;
	Chunk* next = nullptr;
	Chunk* prev = nullptr;
	size_t offset = 0;
	size_t total_size;
};

Chunk::~Chunk()
{
	free(node);
	node = nullptr;
};

template <typename T, size_t total_size = 10>
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

	Chunk* mem_chunk = nullptr;
	bool deallocate_chunk = false;
	//size_t offset = 0;
	size_t total_size = 10;
};

template <typename T, size_t total_size>
MyAllocator<T, total_size>::MyAllocator()
{
	std::cout << "Constructor of MyAllocator" << std::endl;
	mem_chunk = new Chunk(total_size);
}

template <typename T, size_t total_size>
template <typename U>
MyAllocator<T, total_size>::MyAllocator(const MyAllocator<U>& alloc)
{
	// should we make a copy of the rhs.m_buffer ?
	// No, we should not!
	std::cout << "Constructor of MyAllocator T U" << std::endl;
	if (!alloc.deallocate_chunk)
		mem_chunk = alloc.mem_chunk;
}

template <typename T, size_t total_size>
T* MyAllocator<T, total_size>::allocate(std::size_t count)
{
	mem_chunk->node = malloc(total_size * sizeof(T));

	if (!mem_chunk->node)
		throw std::bad_alloc();

	if (mem_chunk->offset + count > total_size)
	{
		mem_chunk->next = new Chunk(total_size + total_size * 2);
		mem_chunk->next->prev = mem_chunk;
		mem_chunk = mem_chunk->next;
		total_size = total_size + total_size * 2;
		mem_chunk->node = malloc(total_size * sizeof(T));
		mem_chunk->offset = 0;
	}

	T* currentAddress = (T*)mem_chunk->node + mem_chunk->offset;
	mem_chunk->offset += count;

	return reinterpret_cast<T*>(currentAddress);
}

template <typename T, size_t total_size>
MyAllocator<T, total_size>::~MyAllocator()
{
	std::cout << "Destructor of Allocator" << std::endl;
	if (mem_chunk && deallocate_chunk)
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

template <typename T, size_t total_size>
void MyAllocator<T, total_size>::deallocate(T* p, std::size_t)
{
	if (p)
		deallocate_chunk = true;
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