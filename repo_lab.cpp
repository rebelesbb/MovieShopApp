#include "repo_lab.h"
#include "_exceptions.h"
#include <random>

const vector<Movie>& RepoLab::getAll() 
{
	movieVector.clear();
	for (const auto& element : movieList)
		movieVector.push_back(element.second);

	return movieVector;
}

const Movie& RepoLab::getMovie(int index) const
{
	return movieList.at(index);
}

int RepoLab::size() const noexcept
{
	return (int)movieList.size();
}

void RepoLab::store(const Movie& new_movie)
{
	generateProb();

	movieList.insert({ current, new_movie });
	current++;
}

void RepoLab::delete_(int index)
{
	generateProb();

	movieList.erase(index);
}

vector<Movie>::const_iterator RepoLab::find(const string& title) 
{
	getAll();

	return std::find_if(movieVector.begin(), movieVector.end(), [title](const Movie& movie) {
		return movie.get_title() == title;
		});
}

void RepoLab::modify(int index, const Movie& modified_movie)
{
	generateProb();

	movieList.at(index) = modified_movie;
}

void RepoLab::insert(int index, const Movie& movie)
{ 
	generateProb();

	movieList.insert({ index, movie });
	current++;
}

void RepoLab::generateProb()
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> dist(0.0, 1.0);
	double prob = dist(generator);

	if (prob < probability)
		throw InvalidPropapilityException();
}
