#include "stdafx.h"

#include <cstdlib>
#include <Windows.h>

#include "windebug.h"

#include "MemoryService.h"


MemoryService::MemoryService(std::size_t pageSize)
	:pageSize(pageSize)
{
}


MemoryService::~MemoryService()
{
	for (const MemoryBlock& block : memoryList)
	{
		VirtualFree(block.ptr, 0, MEM_RELEASE);
	}
}

const std::list<MemoryBlock>& MemoryService::GetAllocations() const
{
	return memoryList;
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

	void* ptr = VirtualAlloc(nullptr, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	ASSERT(ptr != nullptr, "VirtualAlloc failed! Error message: %s", GetLastErrorString().c_str());

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
			bool success = VirtualFree(ptr, 0, MEM_RELEASE);
			ASSERT(success, "VirtualFree failed! Error message: %s.", GetLastErrorString().c_str());
			memoryList.remove(block);
			return;
		}
	}

	ASSERT(false, "%p is invalid ptr to delete!", ptr);

}
