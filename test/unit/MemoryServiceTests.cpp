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

		Assert::AreNotEqual(*(int*)ptr, 8);
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

	TEST_METHOD(DeleteService_HasAllocatedMemory_DeletdUsedMemory)
	{
		MemoryService* service = new MemoryService();
		void* ptr = service->Allocate(sizeof(int));

		int newVal = 8;
		memcpy_s(ptr, sizeof(int), &newVal, sizeof(int));

		delete service;

		Assert::AreNotEqual(*(int*)ptr, 8);
	}
};
