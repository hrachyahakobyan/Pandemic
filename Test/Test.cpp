// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	::testing::GTEST_FLAG(filter) = "StateMachineTest*";
	RUN_ALL_TESTS();
	int a;
	std::cin >> a;
	return 0;
}

