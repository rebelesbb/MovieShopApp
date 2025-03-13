#include "movie_service.h"
#include <algorithm>
using std::sort;

void MovieService::addMovie(const string& title, const string& genre, int year, const string& actor)
{
	const Movie& new_movie{ title, genre, year, actor };
	validator.validateMovie(new_movie);

	repo.store(new_movie);
	undoList.push_back(std::make_unique<UndoAdd>(repo));
}

void MovieService::deleteMovie(int position)
{
	if (repo.size() == 0)
		throw EmptyListException();

	if (position > repo.size() || position < 0)
		throw InvalidPositionException() ;

	Movie deletedMovie = repo.getMovie(position);
	repo.delete_(position);
	undoList.push_back(std::make_unique<UndoDelete>(repo, deletedMovie, position));
}

void MovieService::updateMovie(int position, const string& new_title, const string& new_genre, int year, const string& new_actor)
{
	if (size() == 0)
		throw EmptyListException();

	if (position > size())
		throw InvalidPositionException();

	Movie updated_movie{ new_title, new_genre, year, new_actor };
	validator.validateMovie(updated_movie);

	vector<Movie> movies = repo.getAll();

	for (const Movie& m : movies)
		if (updated_movie.equal(m))
			throw(DuplicateMovieException());

	Movie modifiedMovie = repo.getMovie(position);
	repo.modify(position, updated_movie);
	undoList.push_back(std::make_unique<UndoModify>(repo, modifiedMovie, position));
}

const vector<Movie> MovieService::filterMovies(const string& key, const string& value)
{
	int year_value = 0;
	if (key == "an")
	{
		year_value = stoi(value);
		if (validator.validateYear(year_value) == false)
			throw InvalidYearException();
	}
	else if (key == "titlu")
	{
		if (validator.validateTitle(value) == false)
			throw InvalidTitleException();
	}
	else throw InvalidFilterKeyException();

	vector<Movie> movies = getAll();
	vector<Movie> filtered_list{(unsigned)size()};


	auto it = std::copy_if(movies.begin(), movies.end(), filtered_list.begin(), [year_value, key, value](const Movie& m) {

		return (key == "an" && year_value == m.get_year()) || (key == "titlu" && m.get_title().find(value) != string::npos);

		});

	auto length = std::distance(filtered_list.begin(), it);
	filtered_list.resize(length);

	return filtered_list;
}

const Movie& MovieService::findMovie(string title)
{
	if (!validator.validateTitle(title))
		throw InvalidTitleException();
	vector<Movie>::const_iterator it = repo.find(title);
	if (it == getAll().end())
		throw MovieNotFoundException();
	
	return *it;
}

bool compareYearGenre(const Movie& movie1, const Movie& movie2)
{
	if (movie1.get_year() < movie2.get_year())
		return true;
	else if (movie1.get_year() == movie2.get_year() && movie1.get_genre() < movie2.get_genre())
		return true;
	return false;
}

bool compareTitle(const Movie& movie1, const Movie& movie2)
{
	if (movie1.get_title() < movie2.get_title())
		return true;
	return false;
}

bool compareActor(const Movie& movie1, const Movie& movie2)
{
	if (movie1.get_actor() < movie2.get_actor())
		return true;
	return false;
}

const vector<Movie> MovieService::sortMovies(int key) const
{
	if (repo.getAll().size() == 0)
		throw EmptyListException();

	vector<Movie> sorted_list = getAll();

	if (key == 1)
	{
		sort(sorted_list.begin(), sorted_list.end(), compareTitle);
	}
	else if (key == 2)
	{
		sort(sorted_list.begin(), sorted_list.end(), compareActor);
	}
	else if (key == 3)
	{
		sort(sorted_list.begin(), sorted_list.end(), compareYearGenre);
	}
	else throw InvalidSortKeyException();

	return sorted_list;
}

const map<int, MovieCount> MovieService::generateMoviesByYearReport() const {

	if (size() == 0)
		throw EmptyListException();

	map<int, MovieCount> report;


	for (const auto& movie : getAll())
	{
		const auto it = report.find(movie.get_year());
		if (it == report.end())
			report.insert({ movie.get_year(), MovieCount{movie.get_year(), 1}});
		else report[movie.get_year()].incrementCount();
	}

	return report;

}

void MovieService::addDefault()
{
	vector<string> titles = { "Titanic", "The Shawshank Redemption", "The Godfather", "Forrest Gump",
		"The Dark Knight", "Pulp Fiction", "Schindler's List", "Inception", "The Matrix", "Jurassic Park",
		"Avatar", "The Lord of the Rings: The Return of the King", "Braveheart", "The Silence of the Lambs",
		"Gladiator", "The Avengers", "The Lion King", "The Harry Potter series", "The Social Network", "Interstellar" };
	vector<string> actors = { "Brad Pitt", "Meryl Streep", "Denzel Washington", "Nicole Kidman",
		"Robert Downey Jr.", "Charlize Theron", "Will Smith", "Natalie Portman", "Johnny Depp",
		"Julia Roberts", "Matt Damon", "Cate Blanchett", "George Clooney", "Angelina Jolie",
		"Tom Cruise", "Viola Davis", "Ryan Gosling", "Anne Hathaway", "Samuel L. Jackson", "Sandra Bullock" };
	vector<string> genres = { "Comedie", "Horror", "Actiune", "Drama", "Romance" };
	vector<int> years = { 2000, 1995, 1987, 2010, 1990, 2005, 1975, 2020, 2000, 1965,
		1990, 2015, 2000, 1980, 1995, 2000, 1965, 2020, 1970, 2010 };

	for (int index = 0; index < 20; ++index)
		addMovie(titles[index], genres[index % 5], years[index], actors[index]);
}

void MovieService::addToCart(const string& title)
{
	cart.addToCart(title, getAll());
}

void MovieService::emptyCart()
{
	cart.emptyCart();
}

void MovieService::generateCart(int number)
{
	cart.generateCart(number, getAll());
}

void MovieService::exportHTML(string filename)
{
	cart.exportHTML(filename);
}

const vector<Movie>& MovieService::getAll() const
{
	return repo.getAll();
}

const Movie& MovieService::getMovie(int index) const
{
	return repo.getMovie(index);
}

const int MovieService::getCartSize() const noexcept
{
	return cart.size();
}

const vector<Movie> MovieService::getAllCart() const noexcept
{
	return cart.getAll();
}

const Movie& MovieService::getMovieCart(const int index) const noexcept
{
	return cart.getMovie(index);
}

Cart& MovieService::getCart()
{
	return cart;
}

int MovieService::size() const
{
	return repo.size();
}



void MovieService::undo()
{
	if (undoList.empty())
		throw EmptyUndoListException();
	
	undoList.back()->doUndo();
	undoList.pop_back();
}

