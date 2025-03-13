#include "ui.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::cin;
using std::getline;
using std::ws;
using std::ofstream;


void Console::printMenu()
{
	cout << "Total cos: " << service.getCartSize() << "\n\n";
	cout << "0. COS\n";
	cout << "1. Afisare lista filme\n";
	cout << "2. Adaugare film\n";
	cout << "3. Stergere film\n";
	cout << "4. Actualizare date film\n";
	cout << "5. Cautare film\n";
	cout << "6. Filtrare filme\n";
	cout << "7. Sortare filme\n";
	cout << "8. Generare raport\n";
	cout << "9. Undo\n";
	cout << "10. Iesire\n";

}

void Console::printMovieList(const vector<Movie>& list)
{

	if (list.size() == 0)
		throw EmptyListException();

	cout << '\n';
	int index = 1;
	for(const auto& movie: list)
	{
		cout << index++;
		cout << ". Titlu: " << movie.get_title() << " | ";
		cout << "Gen: " << movie.get_genre() << " | ";
		cout << "An: " << movie.get_year() << " | ";
		cout << "Actor: " << movie.get_actor() << '\n';
	}
	cout << '\n';
}

void Console::addMovieUI()
{
	int year;
	string title, genre, actor;

	cout << "Intorduceti titlu: ", getline(cin >> ws, title);
	cout << "Introduceti gen: " , getline(cin >> ws, genre);
	cout << "Introduceti an: ", cin >> year;
	cout << "Introduecti actor principal: ", getline(cin >> ws, actor);
	cout << '\n';

	try {
		service.addMovie(title, genre, year, actor);
		cout << "Adaugare realizata cu succes!";
	}
	catch (const Exception& err) {
		cout << err.Message;
	}
}

void Console::deleteMovieUI()
{
	int position = 0;
	printMovieList(service.getAll());
	
	cout << "Introduceti numarul filmului: ", cin >> position;
	try {
		service.deleteMovie(position - 1);
		cout << "Stergere realizata cu succes!\n";
	}
	catch (const Exception& err) {
		cout << err.Message;
	}
}

void Console::updateMovieUI()
{
	int position = 0;
	printMovieList(service.getAll());

	cout << "Introduceti numarul filmului: ", cin >> position;

	string new_title, new_genre, new_actor;
	int new_year = 0;

	cout << "\nIntroduceti datele noi:\n";
	cout << "Titlu: ", getline(cin >> ws, new_title);
	cout << "Gen: ", getline(cin >> ws, new_genre);
	cout << "An:", cin >> new_year;
	cout << "Actor: ", getline(cin >> ws, new_actor);

	try {
		service.updateMovie(position - 1, new_title, new_genre, new_year, new_actor);
		cout << "Modificare realizata cu succes!\n";
	}
	catch (const Exception& err) {
		cout << err.Message;
	}
}

void Console::findMovieUI()
{
	string title;
	cout << "Introduceti titlul: ", getline(cin >> ws, title);
	
	try {
		Movie movie = service.findMovie(title);
		cout << "Film gasit!\n";
		cout << "Titlu: " << movie.get_title() << " | ";
		cout << "Gen: " << movie.get_genre() << " | ";
		cout << "An: " << movie.get_year() << " | ";
		cout << "Actor: " << movie.get_actor() << '\n';
	}
	catch (const Exception& err) {
		cout << err.Message;
	}
}

void Console::filterMoviesUI()
{
	string key, value;

	cout << "Introduceti cheia de filtrare (an/titlu)\n>", getline(cin >> ws, key);
	
	if (key == "an") {
		cout << "Introduceti anul: ", getline(cin >> ws, value);
	}
	else if (key == "titlu")
	{
		cout << "Introduceti sirul pe care titlul il contine:\n> ", getline(cin >> ws, value);
	}

	try {
		const vector<Movie>& filtered_list = service.filterMovies(key, value);

		if (key == "an") {
			cout << "Filmele lansate in anul " << value << " sunt:";
		}
		else cout << "Filmele care contin \"" << value << "\" sunt:";
		cout << '\n';
		printMovieList(filtered_list);
	}
	catch (const Exception& err) {
		cout << err.Message;
	}
	
}

void Console::sortMoviesUI()
{
	cout << "\n1.Titlu\n2.Autor\n3.An si gen\nSelectati cheia de sortare:";
	int key;
	cin >> key;
	try
	{
		vector<Movie> sorted_list = service.sortMovies(key);
		cout << '\n';
		printMovieList(sorted_list);
	}
	catch (const Exception& err)
	{
		cout << err.Message;
	}
}

void Console::generateMoviesByYearReportUI()
{
	try {
		map<int, MovieCount> report = service.generateMoviesByYearReport();
		cout << "Raport generat: ";
		for (const auto& element : report)
		{
			cout << "Filme din " << element.first << " : " << element.second.getCount() <<'\n';
		}
	}
	catch (Exception& err)
	{
		cout << err.Message;
	}
}

void Console::printCartMenu()
{
	cout << "\n1. Afisare continut cos\n";
	cout << "2. Adaugare in cos\n";
	cout << "3. Golire cos\n";
	cout << "4. Generare cos\n";
	cout << "5. Export HTML\n";
	cout << "6. Back\n\n";
}

void Console::addToCartUI()
{
	string title;
	cout << "Introduceti titlul filmului pe care doriti sa il aduagati:\n>", getline(cin >> ws, title);
	try {
		service.addToCart(title);
		cout << "Filmul a fost adaugat in cos\n";
	}
	catch (Exception& err) {
		cout << err.Message;
	}
}

void Console::generateCartUI()
{
	int number;
	cout << "Introduceti numarul: ", cin >> number;
	try {
		service.generateCart(number);
		cout << "Cosul a fost generat\n";
	}
	catch (Exception& err) {
		cout << err.Message;
	}
}

void Console::exportHtmlUI()
{
	string filename;

	cout << "Introduceti numele fisierului pentru export:\n";
	cout << "(Este recomandat sa folositi extensia .html)\n>";
	getline(cin >> ws, filename);

	try {
		service.exportHTML(filename);
		cout << "Fisier generat\n";
	}
	catch (Exception& err)
	{
		cout << err.Message;
	}
}

void Console::cartUI()
{
	int option;
	while (true) {
		printCartMenu();
		cout << "Introduceti optiunea: ", cin >> option;
		switch (option)
		{
		case 1:
			try{
				printMovieList(service.getAllCart());
			}
			catch (Exception&) {
				cout << "Cosul este gol\n";
			}
			return;
		case 2:
			addToCartUI();
			return;
		case 3:
			service.emptyCart();
			cout << "Cosul a fost golit\n";
			return;
		case 4:
			generateCartUI();
			return;
		case 5:
			exportHtmlUI();
			return;
		case 6:
			///back
			return;
		default:
			cout << "Optiune invalida\n";
			break;
		}
		cout << '\n';
	}

}


void Console::undoUI()
{
	try {
		service.undo();
		cout << "Undo realizat cu succes!\n";
	}
	catch (Exception& err) {
		cout << err.Message;
	}
}


void Console::run()
{
	//service.addDefault();

	int option;
	while (true) {
		printMenu();
		cout << "Introduceti optiunea: ", cin >> option;
		switch (option)
		{
		case 0:
			cartUI();
			break;
		case 1:
			try{
				printMovieList(service.getAll());
			}
			catch (Exception& err) {
				cout << err.Message;
			}
			break;
		case 2:
			addMovieUI();
			break;
		case 3:
			deleteMovieUI();
			break;
		case 4:
			updateMovieUI();
			break;
		case 5:
			findMovieUI();
			break;
		case 6:
			filterMoviesUI();
			break;
		case 7:
			sortMoviesUI();
			break;
		case 8:
			generateMoviesByYearReportUI();
			break;
		case 9:
			undoUI();
			break;
		case 10:
			//Iesire
			return;
		default:
			cout << "Optiune invalida\n";
			break;
		}
		cout << '\n';
	}
}
