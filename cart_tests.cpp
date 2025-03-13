#include "all_tests.h"
#include "cart.h"
#include <cassert>

void testAddToCart(Cart& cart)
{
	Movie movie1{ "title1", "genre1", 2001, "artist1" };
	Movie movie2{ "title2", "genre2", 2002, "artist2" };
	vector<Movie> movieL({ movie1, movie2});
	
	cart.addToCart("title1", movieL);
	assert(movie1.equal(cart.getMovie(0)));
	
	cart.addToCart("title2", movieL);
	assert(movie2.equal(cart.getMovie(1)));

	try {
		cart.addToCart("title2", movieL);
		assert(false);
	}
	catch(DuplicateMovieException&)
	{
		assert(true);
	}
	
	try
	{
		cart.addToCart("Title3", movieL);
		assert(false);
	}
	catch (MovieNotFoundException&)
	{
		assert(true);
	}

}

void testEmptyCart(Cart& cart)
{
	assert(cart.size() != 0);
	cart.emptyCart();
	assert(cart.size() == 0);
}

void testGenerateRandom(Cart& cart)
{
	assert(cart.size() == 0);

	Movie movie1{ "title1", "genre1", 2001, "artist1" };
	Movie movie2{ "title2", "genre2", 2002, "artist2" };
	Movie movie3{ "title3", "genre3", 2003, "artist3" };

	vector<Movie> movieL({ movie1, movie2, movie3 });

	cart.generateCart(3, movieL);

	assert(cart.size() == 3);

	cart.emptyCart();
	movieL.pop_back();

	try
	{
		cart.generateCart(3, movieL);
		assert(false);
	}
	catch(InsufficientDataException&)
	{
		assert(true);
		assert(cart.size() == 2);
	}

	cart.emptyCart();
	movieL.erase(movieL.begin(), movieL.end());

	assert(movieL.size() == 0);

	try {
		cart.generateCart(3, movieL);
		assert(false);
	}
	catch (EmptyListException&)
	{
		assert(true);
		assert(cart.size() == 0);
	}

}

void testExportHTML(Cart& cart)
{
	assert(cart.size() == 0);
	try
	{
		cart.exportHTML("file");
		assert(false);
	}
	catch (EmptyCartException& err)
	{
		assert(true);
		assert(err.Message == "Cosul este gol");
	}

	Movie movie1{ "title1", "genre1", 2001, "artist1" };
	Movie movie2{ "title2", "genre2", 2002, "artist2" };
	Movie movie3{ "title3", "genre3", 2003, "artist3" };

	vector<Movie> movieL({ movie1, movie2, movie3 });

	cart.generateCart(3, movieL);
	assert(cart.getAll().size() == 3);
	cart.exportHTML("testCart.html");
}

void Tests::testCart()
{
	Cart cart{};
	testAddToCart(cart);
	testEmptyCart(cart);
	testGenerateRandom(cart);
	testExportHTML(cart);
}