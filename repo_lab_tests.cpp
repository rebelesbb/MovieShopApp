#include "all_tests.h"
#include "repo_lab.h"
#include <cassert>
#include "_exceptions.h"


void Tests::testRepoLab()
{
	RepoLab repo1{ 0 };

	assert(repo1.size() == 0);

	repo1.store(Movie{ "Titlu", "Horror", 2000, "Actor" });
	assert(repo1.size() == 1);

	repo1.modify(0, Movie{ "Titlu Nou", "Drama", 2001, "Actor Nou" });
	assert(repo1.getAll().size() == 1);
	assert(repo1.getMovie(0).get_title() == "Titlu Nou");

	auto it = repo1.find("Titlu Nou");

	assert((*it).get_title() == "Titlu Nou");

	repo1.insert(1, Movie{ "Titlu", "Drama", 2001, "Actor Nou" });
	assert(repo1.size() == 2);
	repo1.delete_(0);
	assert(repo1.size() == 1);

	RepoLab repo2{ 1 };

	try
	{
		repo2.store(Movie{ "Titlu Nou", "Drama", 2001, "Actor Nou" });
		assert(false);
	}
	catch (Exception&)
	{
		assert(true);
	}

	try
	{
		repo2.delete_(0);
		assert(false);
	}
	catch (Exception&)
	{
		assert(true);
	}

	try
	{
		repo2.modify(0, Movie{ "Titlu Nou", "Drama", 2001, "Actor Nou" });
		assert(false);
	}
	catch (Exception&)
	{
		assert(true);
	}

	try
	{
		repo2.insert(0, Movie{ "Titlu Nou", "Drama", 2001, "Actor Nou" });
		assert(false);
	}
	catch (Exception&)
	{
		assert(true);
	}

}