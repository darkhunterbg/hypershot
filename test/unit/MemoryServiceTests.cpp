#include "stdafx.h"
#include "CppUnitTest.h"
#include "MemoryService.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS(MemoryServiceTests)
{
public:

	TEST_METHOD(AllocMemory_PositiveValue_ReturnsNonNullPtr)
	{
		std::size_t size = 1024;
		MemoryService serivce;

		void* ptr = serivce.Allocate(size);

		Assert::IsNotNull(ptr);
	}

};
