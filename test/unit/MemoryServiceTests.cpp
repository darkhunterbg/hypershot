#include "stdafx.h"
#include "CppUnitTest.h"
#include "MemoryService.h"
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


TEST_CLASS(MemoryServiceTests)
{
public:

	TEST_METHOD(AllocMemory_PositiveValue_ReturnsNonNullPtr)
	{
		MemoryService serivce;

		void* ptr = serivce.Allocate(1024);

		Assert::IsNotNull(ptr);
	}

	TEST_METHOD(AllocMemory_Zero_ThrowsException)
	{
		Assert::ExpectException<std::exception>([]() {
			MemoryService service;
			service.Allocate(0);
		});
	}

	TEST_METHOD(DeallocMemory_UsedPtr_Deleted)
	{
		MemoryService service;
		void* ptr = service.Allocate(sizeof(int));

		int newVal = 8;
		memcpy_s(ptr, sizeof(int), &newVal, sizeof(int));

		service.Deallocate(ptr);

		Assert::AreEqual((std::size_t)0, service.GetAllocations().size());
	}

	TEST_METHOD(DeallocMemory_Nullptr_ThrowsException)
	{
		Assert::ExpectException<std::exception>([]() {
			MemoryService service;
			service.Deallocate(nullptr);
		});
	}

	TEST_METHOD(DeallocMemory_InvalidPtr_ThrowsException)
	{
		Assert::ExpectException<std::exception>([]() {
			MemoryService service;

			void* ptr = (void*)0x242454;

			service.Deallocate(ptr);
		});
	}

	/*
	TEST_METHOD(DeleteService_HasAllocatedMemory_DeleteUsedMemory)
	{
		MemoryService* service = new MemoryService();
		void* ptr = service->Allocate(sizeof(int));

		int newVal = 8;
		memcpy_s(ptr, sizeof(int), &newVal, sizeof(int));

		delete service;

		Assert::AreEqual((std::size_t)0, service->GetAllocations().size());
	}
	*/
	

	TEST_METHOD(GetAllocations_AllocatedMemory_ReturnsCorrectAllocList)
	{
		MemoryService serivce;
		serivce.Allocate(8);
		serivce.Allocate(24);
		serivce.Allocate(128);

		const std::list<MemoryBlock>& allocs = serivce.GetAllocations();

		Assert::AreEqual((std::size_t)3, allocs.size());

		auto iter = allocs.cbegin();

		Assert::AreEqual((std::size_t)8, iter->size);
		++iter;
		Assert::AreEqual((std::size_t)24, iter->size);
		++iter;
		Assert::AreEqual((std::size_t)128, iter->size);
		++iter;
	}

	TEST_METHOD(CreateService_UsingPageSize_AllocsPageSizeBlock)
	{
		MemoryService service(64);
		service.Allocate(8);

		const MemoryBlock& block = *service.GetAllocations().cbegin();

		Assert::AreEqual((std::size_t)64, block.actualSize);
		Assert::AreEqual((std::size_t)8, block.size);
	}

	TEST_METHOD(CreateService_WithoutPageSize_AllocsExactSizeBlock)
	{
		MemoryService service;
		service.Allocate(8);

		const MemoryBlock& block = *service.GetAllocations().cbegin();

		Assert::AreEqual((std::size_t)8, block.actualSize);
		Assert::AreEqual((std::size_t)8, block.size);
	}
};
