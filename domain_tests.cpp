#include "validator.h"
#include "_exceptions.h"
#include "all_tests.h"
#include <cassert>

void testCreateMovie()
{
	Movie film1{ "Titlu", "gen", 2000, "actor" };
	assert(film1.get_title() == "Titlu");
	assert(film1.get_actor() == "actor");
	assert(film1.get_genre() == "gen");
	assert(film1.get_year() == 2000);

	Movie film2{ "Titlu", "gen", 2000, "actor" };
	assert(film1.equal(film2));
	assert(film2.equal(film1));
}

void testValidator()
{
	Validator validate{};
	assert(validate.validateActor("s") == false);
	assert(validate.validateActor("aghv12") == false);
	assert(validate.validateActor("Actor") == true);

	assert(validate.validateGenre("s") == false);
	assert(validate.validateGenre("Comedie") == true);

	assert(validate.validateTitle("s") == false);
	assert(validate.validateTitle("Titlu") == true);

	assert(validate.validateYear(1000) == false);
	assert(validate.validateYear(2000) == true);

	try{
		validate.validateMovie(Movie{ "Titlu", "Comedie", 2000, "Nume Prenume" });
		assert(true);
	}
	catch (InvalidDataException&) {
		assert(false);
	}

	try {
		validate.validateMovie(Movie{ "s", "s", 1000, "12" });
		assert(false);
	}
	catch (InvalidDataException&) {
		assert(true);
	}

}

void Tests::testDomain()
{
	testCreateMovie();
	testValidator();
}