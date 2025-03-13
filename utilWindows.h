#pragma once
#include <QtWidgets/qlineedit.h>
#include <qmessagebox.h>
#include <qpixmap.h>
#include <fstream>
#include <qlayout.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <vector>
#include "movie_service.h"
#include <qtablewidget.h>
using std::vector;

class SortWindow : public QWidget
{
public:
	SortWindow()
	{
		auto layout = new QVBoxLayout;
		auto centerLy = new QHBoxLayout;
		auto movieDataLy = new QFormLayout;
		layout->addWidget(message);

		centerLy->addWidget(movieList);

		movieDataLy->addRow("Titlu", title);
		movieDataLy->addRow("Gen", genre);
		movieDataLy->addRow("An", year);
		movieDataLy->addRow("Actor", actor);

		centerLy->addLayout(movieDataLy);

		layout->addLayout(centerLy);

		setStyleSheet("background-color: #63433E; color: white;");

		title->setStyleSheet("background-color: white; color: black;");
		genre->setStyleSheet("background-color: white; color: black;");
		year->setStyleSheet("background-color: white; color: black;");
		actor->setStyleSheet("background-color: white; color: black;");

		title->setDisabled(true);
		genre->setDisabled(true);
		year->setDisabled(true);
		actor->setDisabled(true);

		setLayout(layout);
		_connect_();
	}

	void setMovieList(const vector<Movie>& movies) {
		movieVector = movies;
		movieList->clear();
		for (const auto& elem : movies)
			movieList->addItem(QString::fromStdString(elem.get_title()));
	}

	void setLblText(const QString& text)
	{
		message->setText(text);
	}

private:
	vector<Movie> movieVector;

	QLabel* message = new QLabel;
	QListWidget* movieList = new QListWidget;
	QLineEdit* title = new QLineEdit;
	QLineEdit* genre = new QLineEdit;
	QLineEdit* year = new QLineEdit;
	QLineEdit* actor = new QLineEdit;

	void _connect_()
	{
		QObject::connect(movieList, &QListWidget::itemClicked, [&]() {
			Movie currentMovie = movieVector.at(movieList->row(movieList->currentItem()));
			qDebug() << currentMovie.get_title();
			title->setText(QString::fromStdString(currentMovie.get_title()));
			genre->setText(QString::fromStdString(currentMovie.get_genre()));
			year->setText(QString::number(currentMovie.get_year()));
			actor->setText(QString::fromStdString(currentMovie.get_actor()));

			});
	}

};


class FilterWindow : public QWidget
{
public:
	FilterWindow(MovieService& service) : srv{ service }
	{
		initGUI();
		_connect_();
	}

private:
	QComboBox* keyData = new QComboBox;
	QLineEdit* valueData = new QLineEdit;
	QPushButton* doneButton = new QPushButton("&Filtrare");
	QListWidget* movieList = new QListWidget;
	QLineEdit* title = new QLineEdit;
	QLineEdit* genre = new QLineEdit;
	QLineEdit* year = new QLineEdit;
	QLineEdit* actor = new QLineEdit;
	MovieService& srv;
	vector<Movie> movies;

	void initGUI()
	{
		setStyleSheet("background-color: #63433E; color: white;");

		auto mainLy = new QVBoxLayout;
		setLayout(mainLy);

		auto userInputLy = new QFormLayout;

		userInputLy->addRow("Cheie", keyData);
		keyData->setStyleSheet("background-color: white; color: black");
		keyData->setPlaceholderText("--Selectati cheia--");
		keyData->addItem("Titlu");
		keyData->addItem("An");

		userInputLy->addRow("Valoare", valueData);
		valueData->setStyleSheet("background-color: white; color: black");

		mainLy->addLayout(userInputLy);

		mainLy->addWidget(doneButton);

		auto resultLy = new QHBoxLayout;
		resultLy->addWidget(movieList);
		movieList->setStyleSheet("background-color: white; color: black");

		auto movieDataLy = new QFormLayout;

		movieDataLy->addRow("Titlu", title);
		movieDataLy->addRow("Gen", genre);
		movieDataLy->addRow("An", year);
		movieDataLy->addRow("Actor", actor);

		setStyleSheet("background-color: #63433E; color: white;");

		title->setStyleSheet("background-color: white; color: black;");
		genre->setStyleSheet("background-color: white; color: black;");
		year->setStyleSheet("background-color: white; color: black;");
		actor->setStyleSheet("background-color: white; color: black;");

		title->setDisabled(true);
		genre->setDisabled(true);
		year->setDisabled(true);
		actor->setDisabled(true);

		resultLy->addLayout(movieDataLy);
		mainLy->addLayout(resultLy);
	}

	void filteredGUI()
	{
		auto newMainLy = new QHBoxLayout;
		

		newMainLy->addWidget(movieList);
	}

	void _connect_()
	{
		QObject::connect(doneButton, &QPushButton::clicked, [&]() {
			string key = keyData->currentText().toStdString();
			string value = valueData->text().toStdString();

			key[0] = tolower(key[0]);

			qDebug() << key << ' ' << value;
			
			try {
				movies = srv.filterMovies(key, value);

				movieList->clear();
				for (const auto& movie : movies)
					movieList->addItem(QString::fromStdString(movie.get_title()));
			}
			catch (Exception& err)
			{
				QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
			}

			});

		QObject::connect(movieList, &QListWidget::itemClicked, [&]() {
			Movie currentMovie = movies.at(movieList->row(movieList->currentItem()));
			title->setText(QString::fromStdString(currentMovie.get_title()));
			genre->setText(QString::fromStdString(currentMovie.get_genre()));
			year->setText(QString::number(currentMovie.get_year()));
			actor->setText(QString::fromStdString(currentMovie.get_actor()));
			});
	}
	
};


class ReportWindow : public QWidget
{
public:
	ReportWindow(MovieService& service) : srv{ service }
	{
		auto layout = new QVBoxLayout;

		setStyleSheet("background-color: #63433E; color: white;");

		auto reportTable = new QTableWidget(0, 2, this);

		report = srv.generateMoviesByYearReport();

		QStringList headers;
		headers << "Titlu" << "Numar";
		reportTable->setHorizontalHeaderLabels(headers);

		int current = 0;

		for (const auto& elem: report)
		{
			QTableWidgetItem* newItm1 = new QTableWidgetItem(QString::number(elem.first));
			QTableWidgetItem* newItm2 = new QTableWidgetItem(QString::number(elem.second.getCount()));
			reportTable->insertRow(reportTable->rowCount());
			reportTable->setItem(current, 0, newItm1);
			reportTable->setItem(current, 1, newItm2);
			current++;
		}
		layout->addWidget(reportTable);
	}

private:
	MovieService& srv;
	map<int, MovieCount> report;
};