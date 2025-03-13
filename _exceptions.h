#pragma once
#include <string>

class Exception
{
public:

	__declspec (property(get = getMessage)) std::string Message;
	std::string getMessage() const { return message; }

protected:
	std::string message;
};

class InvalidPositionException : public Exception
{
public:
	InvalidPositionException() noexcept { message = "Selectie invalida"; } ;
};

class DuplicateMovieException : public Exception
{
public: 
	DuplicateMovieException() noexcept { message = "Filmul exista deja in lista"; }
};

class InvalidDataException : public Exception
{
public:
	InvalidDataException(string msg) noexcept { message = msg; }
};

class EmptyListException : public Exception
{
public:
	EmptyListException() noexcept { message = "Lista este goala."; }
};

class InvalidFilterKeyException : public Exception
{
public:
	InvalidFilterKeyException() noexcept { message = "Cheie invalida, aceasta poate fi: an, titlu."; }
};

class InvalidYearException : public Exception
{
public:
	InvalidYearException() noexcept { message = "An invalid, acesta trebuie sa fie mai mare de 1900."; }
};

class InvalidTitleException : public Exception
{
public:
	InvalidTitleException() noexcept { message = "Titlu invalid, acesta trebuie sa contina minim 2 caractere."; }
};

class InvalidSortKeyException : public Exception
{
public:
	InvalidSortKeyException() noexcept { message = "Cheie invalida, aceasta poate fi: an, titlu."; }
};

class MovieNotFoundException : public Exception
{
public:
	MovieNotFoundException() noexcept { message = "Filmul nu exista."; }
};

class EmptyCartException : public Exception
{
public:
	EmptyCartException() noexcept { message = "Cosul este gol"; }
};

class InsufficientDataException : public Exception
{
public:
	InsufficientDataException() noexcept { message = "Generare incompleta, nu exista suficiente filme"; }
};

class EmptyUndoListException : public Exception {
public:
	EmptyUndoListException() noexcept { message = "Nu se poate realiza undo"; }
};

class FailedToOpenFileException : public Exception {
public:
	FailedToOpenFileException() noexcept { message = "Fisierul nu a putut fi deschis"; }
};

class InvalidPropapilityException : public Exception
{
public:
	InvalidPropapilityException() noexcept { message = "Probabilitate invalida"; }
};