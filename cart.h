#pragma once
#include "movie_repo.h"
#include "observer.h"

class Cart : public Observable{
private:
	vector<Movie> movieList;
public:
	Cart() noexcept {}

	const int size() const noexcept;
	const vector<Movie> getAll() const noexcept;
	const Movie& getMovie(int position) const noexcept;

	/**
	 * @brief Adds a movie to the cart
	 * @param title : the title of the movie to be added
	 * @param repo : a repository of movies
	 * @throws [MovieNotFoundException] The movie couldn't be found
	 */
	void addToCart(const string& title, vector<Movie> movies);

	/**
	 * @brief Deletes all the movies from the cart
	 */
	void emptyCart() noexcept;

	/**
	 * @brief Generates a cart of random movies
	 * @param number : [int] the number of movies the cart will have
	 * @param movies : [vector<int>] the movies used to fill the cart
	 */
	void generateCart(int number, vector<Movie> movies);

	/**
	 * @brief creates an html file with the content of the cart
	 * @param filename : [string] the name of the export file
	 * @throws [EmptyCartException] The cart is empty
	 */
	void exportHTML(string filename);
};
