#pragma once
#include <vector>
#include <string>
#include "movie.h"
using std::vector;
using std::string;

class Repo
{
public:

	virtual const vector<Movie>& getAll() = 0;
	virtual const Movie& getMovie(int index) const = 0;
	virtual int size() const noexcept = 0;

	virtual void store(const Movie& new_movie) = 0;

	virtual void delete_(int index) = 0;

	virtual vector<Movie>::const_iterator find(const string& title) = 0;

	virtual void modify(int index, const Movie& modified_movie) = 0;

	virtual void insert(int index, const Movie& movie) = 0;

	virtual ~Repo() = default;
};
