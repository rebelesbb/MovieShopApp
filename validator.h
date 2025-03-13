#pragma once
#include "movie.h"
#include <vector>
using std::vector;

class Validator
{
public:
	Validator() noexcept { errors = ""; }
	/**
	 * @brief Validates a given year
	 * @param year : [int] the year
	 * @return : [bool] true if year > 1900, false otherwise
	 */
	bool validateYear(int year);

	/**
	 * @brief Validates a given title
	 * @param title : [string] the title
	 * @return : [bool] true if string isn't empty and has at least two characters, false otherwise
	 */
	bool validateTitle(const string& title);

	/**
	 * @brief Validates a given actor
	 * @param actor : [string] the actor
	 * @return : [bool] true if string isn't empty, has at least two characters and contains only letters, false otherwise
	 */
	bool validateActor(const string& actor);

	/**
	 * @brief Validates a given genre
	 * @param genre : [string] the genre
	 * @return : [bool] true if the genre is: "Comedie", "Horror", "Drama", "Action", "Romance"
	 */
	bool validateGenre(const string& genre);

	/**
	 * @brief Validates a movie
	 * @param movie : [Movie] the specified movie
	 * @throws: [InvalidDataException] if the any of the data doesn't meet the criteria
	 */
	void validateMovie(const Movie& movie);

private:
	string errors;
};