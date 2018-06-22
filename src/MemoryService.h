#pragma once

#include <cstddef>
#include <list>

struct MemoryBlock;

class MemoryService
{
private:

	std::list<MemoryBlock> memoryList;
	std::size_t pageSize;

public:
	MemoryService(std::size_t pageSize = 0);
	~MemoryService();

	void* Allocate(std::size_t size);
	void Deallocate(void* ptr);
};

