#include "all_tests.h"
#include "movie_repo.h"
#include <cassert>

void testStore()
{
	MovieRepository repo{};
	const Movie& movie{ "Titlu", "Gen", 2000, "Actor" };

	repo.store(movie);
	assert(repo.getMovie(0).equal(movie));
	assert(repo.getAll().size() == 1);

	try
	{
		repo.store(movie);
		assert(false);
	}
	catch (DuplicateMovieException&)
	{
		assert(true);
	}
}

void testDelete()
{
	MovieRepository repo{};
	Movie movie{ "Titlu", "Gen", 2000, "Actor" };

	repo.store(movie);
	assert(repo.size() == 1);

	repo.delete_(0);
	assert(repo.size() == 0);
}

void testFind()
{
	MovieRepository repo{};
	Movie movie1{ "Titlu1", "Gen1", 2001, "Actor1" };
	Movie movie2{ "Titlu2", "Gen2", 2002, "Actor2" };
	repo.store(movie1);
	repo.store(movie2);

	vector<Movie>::const_iterator it;

	it = repo.find("Titlu1");
	assert(movie1.equal(*it));

	it = repo.find("Titlu2");
	assert(movie2.equal(*it));

	repo.delete_(0);
	assert(repo.find("Titlu1") == repo.getAll().end());
}

void testModify()
{
	MovieRepository repo{};
	Movie movie1{ "Titlu1", "Gen1", 2001, "Actor1" };
	Movie movie2{ "Titlu2", "Gen2", 2002, "Actor2" };
	repo.store(movie1);

	vector<Movie>::const_iterator it = repo.find("Titlu1");
	assert(it != repo.getAll().end());

	repo.modify(0, movie2);
	assert(repo.find("Titlu1") == repo.getAll().end());
}

void Tests::testRepo()
{
	testStore();
	testDelete();
	testFind();
	testModify();
}