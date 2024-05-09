#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_12_8/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

        TEST_METHOD(TestFilterRestrictedAccessFiles)
        {
            Node* head = nullptr;
            int numRestrictedFiles = 0;

            Node* file1 = new Node();
            file1->fileName = "file1";
            file1->fileSize = 256;
            file1->creationDate = "12.02.2023";
            file1->accessRights = "allowed";
            file1->next = nullptr;

            Node* file2 = new Node();
            file2->fileName = "file2";
            file2->fileSize = 384;
            file2->creationDate = "01.07.2024";
            file2->accessRights = "denied";
            file2->next = nullptr;

            Node* file3 = new Node();
            file3->fileName = "file3";
            file3->fileSize = 512;
            file3->creationDate = "23.11.2022";
            file3->accessRights = "allowed";
            file3->next = nullptr;

            file1->next = file2;
            file2->next = file3;

            Node* filteredList = filterRestrictedAccessFiles(file1, numRestrictedFiles);

            Assert::AreEqual(1, numRestrictedFiles);
            Assert::AreEqual(string("file2"), filteredList->fileName);
            Assert::AreEqual(384, filteredList->fileSize);
            Assert::AreEqual(string("01.07.2024"), filteredList->creationDate);
            Assert::AreEqual(string("denied"), filteredList->accessRights);
            Assert::IsNull(filteredList->next);

            delete file1;
            delete file2;
            delete file3;
            delete filteredList;
        }
	};
}
