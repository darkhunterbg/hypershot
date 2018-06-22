#include "stdafx.h"

#include <cstdlib>

#include "MemoryService.h"


struct MemoryBlock
{
	void* ptr;
	std::size_t size;
	std::size_t actualSize;

public:
	bool operator ==(const MemoryBlock& b) const
	{
		return ptr == b.ptr;
	}
};


MemoryService::MemoryService(std::size_t pageSize)
	:pageSize(pageSize)
{
}


MemoryService::~MemoryService()
{
	for (const MemoryBlock& block : memoryList)
	{
		free(block.ptr);
	}
}

void * MemoryService::Allocate(std::size_t size)
{
	ASSERT(size > 0, "Size must be a positive value!");

	std::size_t allocSize = size;

	if (pageSize)
	{
		int pages = size / pageSize;
		if (size % pageSize > 0)
			++pages;

		allocSize = pages * pageSize;
	}

	void* ptr = malloc(allocSize);

	MemoryBlock block;
	block.ptr = ptr;
	block.size = size;
	block.actualSize = allocSize;

	memoryList.push_back(block);

	return ptr;
}

void MemoryService::Deallocate(void * ptr)
{
	ASSERT(ptr != nullptr, "Cannot delete nullptr!");

	for (const MemoryBlock& block : memoryList)
	{
		if (block.ptr == ptr)
		{
			free(ptr);
			memoryList.remove(block);
			return;
		}
	}

	ASSERT(false, "Invalid ptr to delete!");

}
