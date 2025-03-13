#include "movie.h"

Movie::Movie(string title, string genre, int year, string actor) noexcept:
    title{ std::move(title) }, genre{ std::move(genre) }, year{ year }, actor{ std::move(actor) } {}

int Movie::get_year() const
{
    return this->year;
}

string Movie::get_title() const
{
    return this->title;
}

string Movie::get_genre() const
{
    return this->genre;
}

string Movie::get_actor() const
{
    return this->actor;
}

bool Movie::equal(const Movie& movie2) const {
    if (this->year == movie2.get_year() &&
        this->title == movie2.get_title() &&
        this->actor == movie2.get_actor() &&
        this->genre == movie2.get_genre())
        return true;
    return false;
}
