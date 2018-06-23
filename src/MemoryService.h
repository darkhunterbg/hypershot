#pragma once

#include <cstddef>
#include <list>

struct MemoryBlock
{
	void* ptr;
	std::size_t size;
	std::size_t actualSize;

	inline bool operator ==(const MemoryBlock& b) const
	{
		return ptr == b.ptr;
	}
};

class MemoryService
{
private:

	std::list<MemoryBlock> memoryList;
	std::size_t pageSize;

public:
	MemoryService(std::size_t pageSize = 0);
	~MemoryService();

	const std::list<MemoryBlock>& GetAllocations() const;

	void* Allocate(std::size_t size);
	void Deallocate(void* ptr);
};

