#pragma once

#include "macros.h"

#include <cstddef>


class MemoryService
{
public:
	HSAPI MemoryService();
	HSAPI ~MemoryService();

	HSAPI void* Allocate(std::size_t size);
};

