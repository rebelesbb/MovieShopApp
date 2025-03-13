#include "all_tests.h"
#include "movie_service.h"
#include <cassert>

void Tests::testUndo()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val };

	assert(srv.size() == 0);

	try {
		srv.undo();
		assert(false);
	}
	catch (Exception&)
	{
		assert(true);
	}

	srv.addMovie("Titlu", "Horror", 2000, "Ceva Actor");
	srv.addMovie("Titlu1", "Drama", 2001, "Alt Actor");
	assert(srv.size() == 2);

	srv.updateMovie(1, "Titlu Nou", "Actiune", 2001, "Actor Nou");
	srv.deleteMovie(0);
	srv.deleteMovie(0);

	assert(srv.size() == 0);


	// undo th2 delete actions
	srv.undo();
	assert(srv.size() == 1);
	srv.undo();
	assert(srv.size() == 2);

	// undo the update
	assert(srv.getMovie(1).get_title() == "Titlu Nou");
	srv.undo();
	assert(srv.getMovie(1).get_title() == "Titlu1");

	srv.undo();
	assert(srv.size() == 1);
	srv.undo();
	assert(srv.size() == 0);

}