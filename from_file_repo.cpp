#include "movie_repo.h"
#include <fstream>

MovieRepoFromFile::MovieRepoFromFile(const string& filename) : filename{ filename }
{
	loadFromFile();
}

void MovieRepoFromFile::loadFromFile()
{
	std::ifstream file;
	file.open(filename);

	if (!file.is_open())
		throw FailedToOpenFileException();

	string line, word;

	while (!file.eof())
	{
		getline(file, line);

		if(line.size())
		{
			vector<string> movie_info;

			/// split the string by '|'
			auto found = line.find('|');
			while (found != -1)
			{
				word = line.substr(0, found);
				line.erase(line.begin(), line.begin() + found + 1);

				movie_info.push_back(word);

				found = line.find('|');
			}

			/// only left in line is the actor
			MovieRepository::store(Movie{ movie_info.at(0), movie_info.at(1) ,stoi(movie_info.at(2)), line });

			movie_info.clear();
		}

	}

	file.close();

}

void MovieRepoFromFile::writeToFile()
{
	std::ofstream file;
	file.open(filename);

	// if (!file.is_open())
		// throw FailedToOpenFileException(); ??

	for (const auto& movie : getAll())
	{
		string line;
		line.append(movie.get_title());
		line.append("|");
		line.append(movie.get_genre());
		line.append("|");
		line.append(std::to_string(movie.get_year()));
		line.append("|");
		line.append(movie.get_actor());
		line.append("\n");
		file << line;
	}

	file.close();

}

void MovieRepoFromFile::store(const Movie& new_movie)
{
	MovieRepository::store(new_movie);
	writeToFile();
}

void MovieRepoFromFile::delete_(int index)
{
	MovieRepository::delete_(index);
	writeToFile();
}

void MovieRepoFromFile::modify(int index, const Movie& modified_movie)
{
	MovieRepository::modify(index, modified_movie);
	writeToFile();
}

void MovieRepoFromFile::insert(int index, const Movie& movie)
{
	MovieRepository::insert(index, movie);
	writeToFile();
}
