#pragma once
#include "movie_service.h"
#include "cart.h"

class Console
{
public:
	Console(MovieService& srv) : service{ srv } {}

	void run();

private:
	void printMenu();
	void printMovieList(const vector<Movie>& list);
	void addMovieUI();
	void deleteMovieUI();
	void updateMovieUI();
	void findMovieUI();
	void filterMoviesUI();
	void sortMoviesUI();
	void generateMoviesByYearReportUI();
	void cartUI();
	void printCartMenu();
	void addToCartUI();
	void exportHtmlUI();
	void generateCartUI();
	void undoUI();
	MovieService& service;
};