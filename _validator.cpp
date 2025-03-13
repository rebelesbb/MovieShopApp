#include "validator.h"
#include "_exceptions.h"
#include "iostream"
///error messages

string invalidYearError()
{
	return "An invalid, anul trebuie sa fie > 1900.\n";
}

string invalidTitleError()
{
	return "Titlu invalid, titlu trebuie sa aiba minim 2 caractere.\n";
}

string invalidGenreError()
{
	return "Gen invalid, genul trebuie sa faca parte din lista: Comedie, Horror, Actiune, Drama, Romance\n";
}

string invalidActorError()
{
	return "Actor invalid, actorul trebuie sa aiba minim 2 caractere si doar litere\n";
}

bool Validator::validateYear(int year)
{
	if (year < 1900)
	{
		errors.append(invalidYearError());
		return false;
	}
	return true;
}

bool Validator::validateTitle(const string& title)
{
	if (title.size() < 2)
	{
		errors.append(invalidTitleError());
		return false;
	}
	return true;
}

bool Validator::validateActor(const string& actor)
{
	if (actor.size() < 2)
	{
		errors.append(invalidActorError());
		return false;
	}

	string digits = "0123456789";
	for(int x = 0; x < 10; x++)
	{
		if (actor.find(digits[x])!=string::npos)
		{
			errors.append(invalidActorError());
			return false;
		}
	}
	return true;
}

bool Validator::validateGenre(const string& genre)
{
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	for (const string& g : genres)
		if (genre == g)
			return true;
	errors.append(invalidGenreError());
	return false;
}

void Validator::validateMovie(const Movie& movie)
{
	errors.clear();
	this->validateTitle(movie.get_title());
	this->validateActor(movie.get_actor());
	this->validateGenre(movie.get_genre());
	this->validateYear(movie.get_year());
	if (errors.size())
		throw InvalidDataException(errors);
}