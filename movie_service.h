#pragma once
#include <map>
#include "repo.h"
#include "validator.h"
#include "cart.h"
#include "undo.h"
using std::map;
using std::unique_ptr;

class MovieCount /// DTO
{
public:
	MovieCount() = default;
	MovieCount(int type, int count) : type{ type }, count{ count } {}
	void incrementCount() { this->count++; }
	const int getCount() const { return this->count; } 
private:
	int type;
	int count;
};

class MovieService
{
public:
	MovieService(Repo& repository, Validator& val) : repo{ repository }, validator{ val } {}
	MovieService(const MovieService&) = default;
	int size() const;
	const vector<Movie>& getAll() const;
	const Movie& getMovie(int index) const;

	const int getCartSize() const noexcept;
	const vector<Movie> getAllCart() const noexcept;
	const Movie& getMovieCart(const int index) const noexcept;
	Cart& getCart(); 



	/**
	 * @brief Adds a movie into the list
	 * @param title : [string] the title of the movie
	 * @param genre : [string] the genre of the movie
	 * @param year  : [int] the year of the premiere
	 * @param actor : [string] the main actor
	 * @throws  [InvalidDataException] The date is not valid;
	 *			[DuplicateMovieException] The movie already exists
	 */
	void addMovie(const string& title, const string& genre, int year, const string& actor);

	/**
	 * @brief Deletes a movie from the list
	 * @param position : [int] the position of the movie int the list
	 * @throws [InvalidPositionException] The position > list length;
	 *		   [EmptyListException] The list is empty
	 */
	void deleteMovie(int position);

	/**
	 * @brief Updates a movie from the list
	 * @param position : [int] the position of the movie in the list
	 * @param new_title : [string] the updated title
	 * @param new_genre : [string] the updated genre
	 * @param year : [int] the updated year
	 * @param new_actor : [string] the updated actor
	 * @throws: [EmptyListException] The list is empty; 
	 *			[DuplicateMovieException] The movie already exists;	
	 * 			[InvalidDataException] Any of the data is not valid;
	 *			[InvalidPositionException] The positioon > list lengths
	 */
	void updateMovie(int position, const string& new_title, const string& new_genre, int year, const string& new_actor);

	/**
	 * @brief Finds a movie in the list
	 * @param title : [int] the title of the movie to be found
	 * @return  [Movie] the first found movie that has the specified title, -1 if not found
	 * @throws  [InvalidTitleException] The title is not valid
	 */
	const Movie& findMovie(string title);
	
	/**
	 * @brief Filters the list of movies based on key
	 * @param key : [string] the specified key 
	 * @param value : [string] the value of the key
	 * @return [vector<string>] The filtered list
	 * @throws [EmptyListException] The list is empty
	 *		   [InvalidFilterKeyException] The key isn't valid
	 *		   [InvalidYearException] The year isn't valid
	 *		   [InvalidTitleException] The title isn't valid
	 */
	const vector<Movie> filterMovies(const string& key, const string& value);

	/**
	 * @brief Sorts the movies based on key
	 * @param key : [int] corresponds to the sorting keys (title, actor, year+genre)
	 * @return [DynamicVector] the sorted list
	 * @throws [EmptyListException] The list is empty
	 *		   [InvalidSortKeyException] The key isn't valid
	 */
	const vector<Movie> sortMovies(int key) const;

	const map<int, MovieCount> generateMoviesByYearReport() const;

	void addDefault();

	/**
	 * @brief Adds a movie to the cart
	 * @param title : the title of the movie to be added
	 * @param repo : a repository of movies
	 * @throws [MovieNotFoundException] The movie couldn't be found
	 */
	void addToCart(const string& title);

	/**
	 * @brief Deletes all the movies from the cart
	 */
	void emptyCart();

	/**
	 * @brief Generates a cart of random movies
	 * @param number : [int] the number of movies the cart will have
	 * @param movies : [vector<int>] the movies used to fill the cart
	 */
	void generateCart(int number);

	/**
	 * @brief creates an html file with the content of the cart
	 * @param filename : [string] the name of the export file
	 * @throws [EmptyCartException] The cart is empty
	 */
	void exportHTML(string filename);

	void undo();

private:
	Cart cart;
	vector<unique_ptr<UndoAction>> undoList;
	Repo& repo;
	Validator& validator;
};

bool compareYearGenre(const Movie& movie1, const Movie& movie2);