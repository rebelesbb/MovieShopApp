#pragma once
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qcombobox.h>
#include <qpixmap.h>
#include "movie_service.h"
#include <qlabel.h>
#include <qlineedit.h>
#include "utilWindows.h"
#include "myModel.h"
#include <qlistview.h>

class AppGUI : public QWidget
{
public:
	AppGUI(MovieService& service);

	const vector<Movie>& getData();

	~AppGUI();

private:

	/// buttons
	QPushButton* addButton = new QPushButton("&Adauga");
	QPushButton* deleteButton = new QPushButton("&Sterge");
	QPushButton* modifyButton = new QPushButton("&Modifica");
	QPushButton* exitButton = new QPushButton("&Exit");
	QPushButton* undoButton = new QPushButton;
	QPushButton* cartButton = new QPushButton;
	QPushButton* addToCartButton = new QPushButton;
	QPushButton* emptyCartButton = new QPushButton;

	/// used for cart
	QPixmap cartImg{".\\cart.png"};
	QIcon* cartIcon = new QIcon(cartImg);

	/// used for undo
	QPixmap undoImg{ "./undo.png" };
	QIcon* undoIcon = new QIcon(undoImg);

	/// line edits and spin boxes for user input
	QLineEdit* titleData = new QLineEdit;
	QComboBox* yearData = new QComboBox;
	QComboBox* genreData = new QComboBox;
	QLineEdit* actorData = new QLineEdit;

	// used for actions that need the position of the current item in the list
	int currentMovie = -1;

	// used for the menu and the menuBar (sort, filter, report actions)
	QAction* sortTitleAction = new QAction("Titlu");
	QAction* sortActorAction = new QAction("Actor");
	QAction* sortYearGenreAction = new QAction("An + Gen");

	QAction* filterAction = new QAction("Filtrare");

	QAction* reportAction = new QAction("Raport");

	QAction* generateCartAction = new QAction("Generare Cos");

	// cartCrudGUI and cartRdOnly bttns

	QPushButton* cartCrudGUIBttn = new QPushButton("&CartCrudGUI");
	QPushButton* cartReadOnlyBttn = new QPushButton("&CartReadOnly");

	MovieService& srv;
	SortWindow sortWin; // the sort window
	FilterWindow filterWin{ srv }; // the filter window

	MyModel* model = new MyModel(srv.getAll());
	QListView* movieList = new QListView;
	//QListWidget* movieList = new QListWidget;

	void initGUI();
	void _connect();
	void loadData();

};