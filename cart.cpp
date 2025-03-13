#include "cart.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>
using std::mt19937; /// generates a random sequence of numbers with a period of 2^19937-1
using std::uniform_int_distribution; /// its member function gives random integer numbers or discrete
									/// values from a given input range with uniform probability
using std::shuffle;
using std::ofstream;

const int Cart::size() const noexcept
{
	return (int)movieList.size();
}

const vector<Movie> Cart::getAll() const noexcept
{
	return movieList;
}

const Movie& Cart::getMovie(int position) const noexcept
{
	return movieList.at(position);
}

void Cart::addToCart(const string& title, vector<Movie> movies)
{
	vector<Movie>::iterator it = std::find_if(movies.begin(), movies.end(), [title, movies](const Movie& movie) {
		return movie.get_title() == title;
		});

	if (it == movies.end())
		throw MovieNotFoundException();

	auto it_ = std::find_if(movieList.begin(), movieList.end(), [title, movies](const Movie& movie) {
		return movie.get_title() == title; 
		});

	if (it_ != movieList.end())
		throw DuplicateMovieException();

	movieList.push_back(*it);
	notify();
}

void Cart::emptyCart() noexcept
{
	while (!movieList.empty())
		movieList.erase(movieList.begin());
	notify();
}

void Cart::generateCart(int number, vector<Movie> movies)
{
	/*
	mt19937 mt{ std::random_device{}() }; /// std::random_device also gives a random number, the we can use as seed for mt
	uniform_int_distribution<> dist(0, movies.size() - 1);
	for (int i = 0; i < number; i++)
	{
		store(movies.at(dist(mt)));
	}
	*/

	if (movies.size() == 0)
		throw EmptyListException();

	shuffle(movies.begin(), movies.end(), std::default_random_engine(std::random_device{}()));
	while (movieList.size() < number && movies.size() > 0)
		movieList.push_back(movies.back()), movies.pop_back();

	if (movieList.size() != number && movies.size() == 0)
		throw InsufficientDataException();

	notify();
}

void Cart::exportHTML(string filename)
{
	if (size() == 0)
		throw EmptyCartException();

	ofstream file;
	file.open(filename);

	file << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
	file << "\t<meta charset=\"UTF-8\">\n";
	file << "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"; 
	file << "\t<title>Shopping Cart</title>\n";
	file << "\t<style>\n";
	file << "\t\tbody{\n\t\t\tbackground-color: #bacdff; \n\t\t}\n";
	file << "\t\ttable{\n\t\t\tborder-collapse: collapse; \n\t\t\tborder: 2px solid black; \n\t\t\tbackground-color: #d7cdff; \n\t\t}\n";
	file << "\t\ttd{\n\t\t\tpadding: 8px; \n\t\t}\n";
	file << "\t</style>\n";
	file << "</head>\n<body>\n\n";
	file << "<h2>Shopping Cart</h2>\n<table border=\"1\">\n";
	for (const auto& movie : movieList)
	{
		file << "\t<tr>\n";
		file << "\t\t<td>\n";
		file << "\t\t\t<p>Titlu: " << movie.get_title() << "</p>\n";
		file << "\t\t\t<p>Gen: " << movie.get_genre() << "</p>\n";
		file << "\t\t\t<p>An: " << movie.get_year() << "</p>\n";
		file << "\t\t\t<p>Actor: " << movie.get_actor() << "</p>\n";
		file << "\t\t</td>\n";
		file << "\t</tr>\n";
	}
	file << "</table>\n\n</body>\n</html>";
	file.close();
}