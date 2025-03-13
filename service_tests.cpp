#include "movie_service.h"
#include "all_tests.h"
#include <cassert>
#include <iostream>

void testAddMovie(MovieService& srv) 
{
	assert(srv.size() == 0);
	srv.addMovie("Titlu", "Comedie", 2000, "Actor");
	assert(srv.getAll().size() == 1);
	srv.addMovie("Titlu 2", "Horror", 2001, "Alt Actor");
	assert(srv.size() == 2);
	assert(srv.getMovie(1).get_year() == 2001);

	try{
		srv.addMovie("Titlu", "Comedie", 2000, "Actor");
		assert(false);
	}
	catch (DuplicateMovieException&) {
		assert(true);
	}

	try {
		srv.addMovie("T", "C", 100, "16");
		assert(false);
	}
	catch (InvalidDataException&)
	{
		assert(true);
	}
	
}

void testDeleteMovie(MovieService& srv)
{
	//we kept the movie from add
	assert(srv.size() == 2);

	try {
		srv.deleteMovie(8);
		assert(false);
	}
	catch(InvalidPositionException&){
		assert(true);
	}

	srv.deleteMovie(0);
	assert(srv.size() == 1);
	assert(srv.getMovie(0).get_year() == 2001);
	
	srv.deleteMovie(0);
	assert(srv.size() == 0);

	try{
		srv.deleteMovie(0);
		assert(false);
	}
	catch (EmptyListException&) {
		assert(true);
	}
}

void testUpdateMovie()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val };
	assert(srv.size() == 0);

	try {
		srv.updateMovie(0, "title", "horror", 2000, "actor");
		assert(false);
	}
	catch (EmptyListException&)
	{
		assert(true);
	}

	///adding some movies into the list
	vector<string> titles = { "Aaaa", "Bbbb", "Aabb", "Cccc","Cddd", "Dddd" };
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	vector<string> actors = { "Jennifer Lawrence", "Tom Hanks", "Emma Stone", "Leonardo DiCaprio", "Scarlett Johansson", "Chris Hemsworth" };
	for (int index = 2000; index <= 2004; index++)
		srv.addMovie(titles[index % 10], genres[index % 10], index, actors[index % 10]);
	srv.addMovie(titles[5], genres[1], 2004, actors[4]);
	
	srv.updateMovie(5, titles[5], genres[1], 2004, actors[5]);
	assert(srv.getMovie(5).get_actor() == actors[5]);


	try{
		srv.updateMovie(5, titles[5], genres[1], 2004, actors[5]);
		assert(false);
	}
	catch (DuplicateMovieException&){
		assert(true);
	}


	try {
		srv.updateMovie(10, titles[5], genres[1], 2004, actors[5]);
		assert(false);
	}
	catch (InvalidPositionException&){
		assert(true);
	}


	try {
		srv.updateMovie(3, titles[5], "asghdv", 2004, actors[5]);
		assert(false);
	}
	catch (InvalidDataException&) {
		assert(true);
	}

}

void testFilterMovies()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val };
	///adding some movies into the list
	vector<string> titles = { "Aaab", "Bbbb", "Aaac", "Cccc","Aaad", "Dddd" };
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	vector<string> actors = { "Jennifer Lawrence", "Tom Hanks", "Emma Stone", "Leonardo DiCaprio", "Scarlett Johansson", "Chris Hemsworth" };
	for (int index = 2000; index <= 2004; index++)
		srv.addMovie(titles[index % 10], genres[index % 10], index, actors[index % 10]);
	srv.addMovie(titles[5], genres[1], 2004, actors[5]);

	vector<Movie> filtered_list;


	try {
		filtered_list = srv.filterMovies("an", "80");
		assert(false);
	}
	catch (InvalidYearException&){
		assert(true);
	}


	try {
		filtered_list = srv.filterMovies("titlu", "a");
		assert(false);
	}
	catch (InvalidTitleException&) {
		assert(true);
	}


	try {
		filtered_list = srv.filterMovies("ads", "jhas");
		assert(false);
	}
	catch (InvalidFilterKeyException&) {
		assert(true);
	}

	filtered_list = srv.filterMovies("an", "2004");
	assert(filtered_list.size() == 2);
	assert(filtered_list.at(0).get_year() == 2004);
	assert(filtered_list.at(1).get_year() == 2004);

	filtered_list = srv.filterMovies("titlu", "Aaa");
	assert(filtered_list.size() == 3);

}

void testFindMovie()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val };
	vector<string> titles = { "Aaab", "Bbbb", "Aaac", "Cccc","Aaac", "Dddd" };
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	vector<string> actors = { "Jennifer Lawrence", "Tom Hanks", "Emma Stone", "Leonardo DiCaprio", "Scarlett Johansson", "Chris Hemsworth" };
	for (int index = 2000; index <= 2004; index++)
		srv.addMovie(titles[index % 10], genres[index % 10], index, actors[index % 10]);
	srv.addMovie(titles[5], genres[0], 2004, actors[5]);


	assert(srv.findMovie("Bbbb").equal(Movie{ "Bbbb", "Horror", 2001, "Tom Hanks"}));
	assert(srv.findMovie("Aaac").equal(Movie{ "Aaac", "Actiune", 2002, "Emma Stone" }));
	
	
	try{
		srv.findMovie("!");
		assert(false);
	}
	catch (InvalidTitleException&) {
		assert(true);
	}

	try {
		srv.findMovie("ajdhbdakub");
		assert(false);
	}
	catch (MovieNotFoundException&) {
		assert(true);
	}

}

void testSortMovies()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val };
	vector<string> titles = { "Aaab", "Bbbb", "Aaac", "Cccc","Aaac", "Dddd" };
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	vector<string> actors = { "Jennifer Lawrence", "Tom Hanks", "Emma Stone", "Leonardo DiCaprio", "Scarlett Johansson", "Chris Hemsworth" };
	
	for (int index = 2000; index <= 2004; index++)
		srv.addMovie(titles[index % 10], genres[index % 10], index, actors[index % 10]);
	srv.addMovie(titles[5], genres[0], 2004, actors[5]);

	vector<Movie> sorted_list = srv.sortMovies(1); //title
	
	assert(sorted_list.at(0).get_title() == "Aaab");
	assert(sorted_list.at(1).get_title() == "Aaac");
	assert(sorted_list.at(2).get_title() == "Aaac");
	assert(sorted_list.at(3).get_title() == "Bbbb");
	assert(sorted_list.at(4).get_title() == "Cccc");
	assert(sorted_list.at(5).get_title() == "Dddd");

	assert(sorted_list.at(1).get_actor() == "Emma Stone");
	assert(sorted_list.at(2).get_actor() == "Scarlett Johansson");
	

	sorted_list = srv.sortMovies(2); //actor
	assert(sorted_list.at(0).get_actor() == "Chris Hemsworth");
	assert(sorted_list.at(1).get_actor() == "Emma Stone");
	assert(sorted_list.at(2).get_actor() == "Jennifer Lawrence");
	assert(sorted_list.at(3).get_actor() == "Leonardo DiCaprio");
	assert(sorted_list.at(4).get_actor() == "Scarlett Johansson");
	assert(sorted_list.at(5).get_actor() == "Tom Hanks");

	srv.addMovie("Title", "Actiune", 2000, "Someone");
	sorted_list = srv.sortMovies(3); //year + genre
	assert(sorted_list.at(0).get_year() == 2000 && sorted_list.at(0).get_genre() == "Actiune");
	assert(sorted_list.at(1).get_year() == 2000 && sorted_list.at(1).get_genre() == "Comedie");
	assert(sorted_list.at(2).get_year() == 2001 && sorted_list.at(2).get_genre() == "Horror");
	assert(sorted_list.at(3).get_year() == 2002 && sorted_list.at(3).get_genre() == "Actiune");
	assert(sorted_list.at(4).get_year() == 2003 && sorted_list.at(4).get_genre() == "Drama");
	assert(sorted_list.at(5).get_year() == 2004 && sorted_list.at(5).get_genre() == "Comedie");
	assert(sorted_list.at(6).get_year() == 2004 && sorted_list.at(6).get_genre() == "Romance");

	MovieRepository repo1{};
	Validator val1{};
	MovieService srv2{ repo1 , val1 };
	Movie movie1("Movie1", "Horror", 2010, "Actor");
	Movie movie2("Movie2", "Horror", 2021, "Actori");
	assert(compareYearGenre(movie1, movie2));

	try {
		srv.sortMovies(4);
		assert(false);
	}
	catch (Exception&) {
		assert(true);
	}

	while (srv.size())  //empty the list
		srv.deleteMovie(0);
	assert(srv.size() == 0);

	try {
		srv.sortMovies(1);
		assert(false);
	}
	catch (const Exception& err) {
		assert(true);
		assert(err.getMessage() == "Lista este goala.");
	}
	
}

void testReport()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val };
	vector<string> titles = { "Aaab", "Bbbb", "Aaac", "Cccc","Aaac", "Dddd" };
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	vector<string> actors = { "Jennifer Lawrence", "Tom Hanks", "Emma Stone", "Leonardo DiCaprio", "Scarlett Johansson", "Chris Hemsworth" };

	for (int index = 2000; index <= 2004; index++)
		srv.addMovie(titles[index % 10], genres[index % 10], index, actors[index % 10]);
	srv.addMovie(titles[5], genres[0], 2004, actors[5]);

	map<int, MovieCount> report = srv.generateMoviesByYearReport();

	assert(report[2004].getCount() == 2);

	while (srv.size())
		srv.deleteMovie(0);

	assert(!srv.size());

	try {
		srv.generateMoviesByYearReport();
		assert(false);
	}
	catch (Exception&){
		assert(true);
	}
}

void testCartFromService()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val }; 
	srv.addDefault();

	assert(srv.getCartSize() == 0);

	srv.addToCart("Titanic");
	assert(srv.getCartSize() == 1);
	srv.addToCart("The Lion King");
	assert(srv.getCartSize() == 2);

	assert(srv.getMovieCart(0).get_title() == "Titanic");
	assert(srv.getAllCart().size() == 2);

	srv.emptyCart();
	assert(srv.getCartSize() == 0);

	srv.generateCart(5);
	assert(srv.getCartSize() == 5);

	srv.exportHTML("testCartFromFile.html");

}

void Tests::testService()
{
	MovieRepository repo{};
	Validator val{};
	MovieService srv{ repo, val};

	testAddMovie(srv);
	testDeleteMovie(srv);
	testUpdateMovie();
	testFilterMovies();
	testFindMovie();
	testSortMovies();
	testReport();
	testCartFromService();
	
}