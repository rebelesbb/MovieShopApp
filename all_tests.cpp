#include "all_tests.h"

Tests::Tests() noexcept
{
	testDomain();
	testRepo();
	testService();
	testCart();
	testUndo();
	testFileRepo();
	testRepoLab();
}