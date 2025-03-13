#pragma once
#include "repo.h"
#include "movie.h"
#include "_exceptions.h"
#include "dynamic_vector.h"
#include <vector>
using std::vector;
using std::unique_ptr;

class MovieRepository : public Repo
{
	//friend class UndoDelete;

public:
	MovieRepository() noexcept = default;

	//Returns the list of movies
	const vector<Movie>& getAll();
	//Returns the movie from the specified index
	const Movie& getMovie(int index) const;
	int size() const noexcept;

	/**
	 * @brief Stores a movie into the list
	 * @param new_movie : [Movie] the movie to be stored
	 * @throws [RepoException] The movie already exists in the list
	 */
	void store(const Movie& new_movie);

	/**
	 * @brief Deletes a movie from the list
	 * @param index : [int] the position of the movie in the list
	 */
	void delete_(int index);

	/**
	 * @brief Finds a movie from th list
	 * @param title : [string] the title of the movie to be found
	 * @return [int] The position of the first occurence of a movie with the specified title in the list, -1 if not found

	 */
	vector<Movie>::const_iterator find(const string& title);

	/**
	 * @brief Modifies a movie from the list
	 * @param index : [int] the position of the movie to be modified
	 * @param modified_movie : [Movie] the movie with the modified data
	 */
	void modify(int index, const Movie& modified_movie);

	/**
	 * @brief Inserts a movie into the listv on the specified position
	 * @param index : [int] the position where we want to insert the movie
	 * @param modified_movie : [Movie] the movie 
	 */
	void insert(int index, const Movie& movie);

private:
	vector<Movie> movieList;
};



class MovieRepoFromFile : public MovieRepository {

public:
	MovieRepoFromFile(const string& filename);

	/**
	 * @brief Stores a movie into the list
	 * @param new_movie : [Movie] the movie to be stored
	 * @throws [RepoException] The movie already exists in the list
	 */
	void store(const Movie& new_movie);

	/**
	 * @brief Deletes a movie from the list
	 * @param index : [int] the position of the movie in the list
	 */
	void delete_(int index);

	/**
	 * @brief Modifies a movie from the list
	 * @param index : [int] the position of the movie to be modified
	 * @param modified_movie : [Movie] the movie with the modified data
	 */
	void modify(int index, const Movie& modified_movie);

	/**
	 * @brief Inserts a movie into the listv on the specified position
	 * @param index : [int] the position where we want to insert the movie
	 * @param modified_movie : [Movie] the movie
	 */
	void insert(int index, const Movie& movie);

private:
	string filename;

	void loadFromFile();
	void writeToFile();

};



