#include "stdafx.h"

#include <cstdlib>
#include <exception>

#include "MemoryService.h"


MemoryService::MemoryService()
{
}


MemoryService::~MemoryService()
{
}

void * MemoryService::Allocate(std::size_t size)
{
	return std::malloc(size);
}
