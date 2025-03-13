#include "all_tests.h"
#include "movie_repo.h"
#include <cassert>

void Tests::testFileRepo()
{
	try
	{
		MovieRepoFromFile repo{"nonexistentfile.txt"};
		assert(false);
	}
	catch (FailedToOpenFileException&)
	{
		assert(true);
	}

	MovieRepoFromFile repo{ "test.txt" };

	assert(repo.size() == 5);

	repo.store(Movie{ "Title", "Horror", 2000, "Actor" });
	assert(repo.getAll().size() == 6);

	repo.delete_(5);
	assert(repo.size() == 5);

	repo.insert(0, Movie{ "Title", "Horror", 2000, "Actor" });
	assert(repo.getAll().size() == 6);

	repo.delete_(0);
	assert(repo.size() == 5);

	repo.modify(4, Movie{ "Title", "Horror", 2000, "Actor" });
	assert(repo.getMovie(4).get_title() == "Title");

	repo.modify(4, Movie{ "The Dark Knight", "Romance", 1990, "Robert Downey Jr." });
}
