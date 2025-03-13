#pragma once

class Tests
{
public:
	Tests() noexcept;

private:
	void testDomain();
	void testRepo();
	void testService();
	void testCart();
	void testUndo();
	void testFileRepo();
	void testRepoLab();
};