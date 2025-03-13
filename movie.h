#pragma once
#include <string>
#include <iostream>

using std::string;

class Movie {
public:
    Movie() noexcept: year{0}{}
    Movie(string title, string genre, int year, string actor) noexcept;

    int get_year() const;

    string get_title() const;

    string get_genre() const;

    string get_actor() const;

    bool equal(const Movie& movie2) const;

    void print();

private:
    string title;
    string genre;
    int year;
    string actor;
};