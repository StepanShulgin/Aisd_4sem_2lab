#include "pch.h"
#include "CppUnitTest.h"

#include "C:\Users\stepa\source\repos\Aisd_4sem_2lab\Aisd_4sem_2lab\MyMap.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2lab
{
	TEST_CLASS(UnitTest2lab)
	{
	public:
		
		TEST_METHOD(isInMapTest)
		{
			MyMap<int, int> TestMap;

			TestMap.insert(33, 10);
			Assert::IsTrue(TestMap.isInMap(33) == 1);
			Assert::IsTrue(TestMap.isInMap(55) == 0);
			
		}
		

		TEST_METHOD(encodingTheStatement)
		{
			MyMap<char, int>TestMap;

			TestMap.insert('a', 1);
			TestMap.insert('b', 1);
			TestMap.insert('c', 1);
			TestMap.insert('d', 1);
			

			int languagePower = 5;

			string statement = "dcba";


			Coding Test(TestMap, languagePower, statement);

			Test.encodingTheStatement(0, 4);
			Assert::IsTrue(Test.encodeTheStatement() == "11100100");
		}

		
		TEST_METHOD(decodingTheStatement)
		{
			MyMap<char, int>TestMap;

			TestMap.insert('a', 1);
			TestMap.insert('b', 1);

			int languagePower = 2;

			string statement = "ba";


			Coding Test(TestMap, languagePower, statement);

			Test.encodingTheStatement(0, 1);
			Assert::IsTrue(Test.encodeTheStatement() == "10");
			Assert::IsTrue(Test.decodeTheStatement() == "ba");
		}

		TEST_METHOD(BubbleSortTest)
		{
			MyMap<char, int> TestMap;

			TestMap.insert('a', 1);
			TestMap.insert('b', 2);
			TestMap.insert('c', 3);

			int languagePower = 3;

			string statement = "acccbb";

			Coding Test(TestMap,languagePower, statement);

			Test.encodingTheStatement(0, 2);

			Assert::IsTrue(Test.encodeTheStatement() == " 110001010");
			Assert::IsTrue(Test.decodeTheStatement() == "acccbb");
		}
		
		TEST_METHOD(encodingTheStatement)
		{
			MyMap<char, int>TestMap;

			TestMap.insert('a', 1);
			TestMap.insert('b', 1);

			int languagePower = 2;

			string statement = "ba";


			Coding Test(TestMap, languagePower, statement);

			Test.encodingTheStatement(0,1);
			Assert::IsTrue(Test.encodeTheStatement() == "10");
		}
	};
}
