#include "movie_repo.h"
#include "_exceptions.h"

void MovieRepository::store(const Movie& new_movie)
{
	for (const Movie& m : movieList)
	{
		if (new_movie.equal(m))
			throw DuplicateMovieException();
	}
	this->movieList.push_back(new_movie);
}

void MovieRepository::delete_(int index)
{
	this->movieList.erase(movieList.begin() + index);
}

vector<Movie>::const_iterator MovieRepository::find(const string& title) 
{
	return std::find_if(movieList.begin(), movieList.end(), [title](const Movie& movie) {
		return movie.get_title() == title;
		});
}

void MovieRepository::modify(int index, const Movie& modified_movie)
{
	this->movieList.at(index) = modified_movie; // at(index) = modified_movie
}

void MovieRepository::insert(int index, const Movie& movie)
{
	this->movieList.insert(movieList.begin() + index, movie);
}

const vector<Movie>& MovieRepository::getAll()
{
	return this->movieList;
}

const Movie& MovieRepository::getMovie(int index) const
{
	return this->movieList.at(index);
}

int MovieRepository::size() const noexcept
{
	return (int)this->movieList.size();
}