#pragma once
#include <vector>
#include <string>
#include <map>
#include "movie.h"
#include "repo.h"
using std::vector;
using std::string;
using std::map;

class RepoLab : public Repo
{
public:

	RepoLab(double prob) noexcept : probability{ prob }, current{ 0 } {}

	const vector<Movie>& getAll() override;
	const Movie& getMovie(int index) const override;
	int size() const noexcept override;

	void store(const Movie& new_movie) override;

	void delete_(int index) override;

	vector<Movie>::const_iterator find(const string& title) override;

	void modify(int index, const Movie& modified_movie) override;

	void insert(int index, const Movie& movie) override;

	void generateProb();

private:
	double probability;
	int current;
	map<int, Movie> movieList;
	vector<Movie> movieVector;
};