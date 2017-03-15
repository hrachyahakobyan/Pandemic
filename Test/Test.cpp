// Test.cpp : Defines the entry point for the console application.
//

#pragma once
#include "stdafx.h"
#include "GuiTest.h"

int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	pan::GuiTest guitest = pan::GuiTest();

	int a;
	std::cin >> a;

	return 0;
}

