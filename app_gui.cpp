#include "app_gui.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qmenubar.h>
#include <QtWidgets/qmenu.h>
#include <qfile.h>
#include <qspinbox.h>

#include "cartWindow.h"
#include "CartCrudGUI.h"
#include "cartReadOnly.h"

AppGUI::AppGUI(MovieService& service) : srv{ service } {
	initGUI();
	_connect();
	loadData();
}

const vector<Movie>& AppGUI::getData()
{
	return srv.getAll();
}

void AppGUI::initGUI()
{
	QFile styleFile("style.qss");
	styleFile.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(styleFile.readAll());

	setStyleSheet(styleSheet);
	setWindowTitle("Gestionare Filme");
	
	auto mainLy = new QVBoxLayout;
	setLayout(mainLy);

	QLabel* menuImgLbl = new QLabel;
	QPixmap menuImg(".\\_film_.png");
	menuImgLbl->setPixmap(menuImg);
	menuImgLbl->setAlignment(Qt::AlignCenter);

	QIcon appIcon(menuImg);
	setWindowIcon(appIcon);

	mainLy->addWidget(menuImgLbl);
	
	auto centerLy = new QHBoxLayout;

	//centerLy->addWidget(movieList);
	centerLy->addWidget(movieList);
	
	auto userInputLy = new QFormLayout;

	/// add the genres and years to the combobox

	genreData->setPlaceholderText("--Selectati Gen--");
	yearData->setPlaceholderText("--Selectati An--");

	genreData->addItem("Horror");
	genreData->addItem("Drama");
	genreData->addItem("Actiune");
	genreData->addItem("Romance");
	genreData->addItem("Comedie");

	for (int i = 2024; i >= 1900; --i)
		yearData->addItem(QString::number(i));

	userInputLy->addRow("Titlu", titleData);
	userInputLy->addRow("An", yearData);
	userInputLy->addRow("Gen", genreData);
	userInputLy->addRow("Actor", actorData);

	auto bttnsLy = new QHBoxLayout;
	bttnsLy->addWidget(addButton);
	bttnsLy->addWidget(deleteButton);
	bttnsLy->addWidget(modifyButton);
	bttnsLy->addWidget(exitButton);

	auto cartBttnLy = new QHBoxLayout;
	cartBttnLy->addWidget(cartCrudGUIBttn);
	cartBttnLy->addWidget(cartReadOnlyBttn);

	auto interactiveSideLy = new QVBoxLayout;

	interactiveSideLy->addLayout(userInputLy);
	interactiveSideLy->addLayout(bttnsLy);
	interactiveSideLy->addLayout(cartBttnLy);
	
	centerLy->addSpacing(20);
	centerLy->addLayout(interactiveSideLy);
	centerLy->addSpacing(20);

	auto rightLy = new QVBoxLayout;

	auto cartHelpLy = new QVBoxLayout;
	cartButton->setIcon(*cartIcon);
	cartHelpLy->addWidget(cartButton);

	QPixmap cartAddImg("./plus.png");
	QIcon* cartAddIcon = new QIcon(cartAddImg);
	addToCartButton->setIcon(*cartAddIcon);

	QPixmap emptyCartImg("./bin.png");
	QIcon* emptyCartIcon = new QIcon(emptyCartImg);
	emptyCartButton->setIcon(*emptyCartIcon);

	cartHelpLy->addWidget(addToCartButton);
	cartHelpLy->addWidget(emptyCartButton);

	cartHelpLy->setAlignment(Qt::AlignTop);
	rightLy->addLayout(cartHelpLy);


	auto undoLy = new QVBoxLayout;

	undoButton->setIcon(*undoIcon);

	undoLy->addWidget(undoButton);
	rightLy->addLayout(undoLy);

	centerLy->addLayout(rightLy);

	auto menuBar = new QMenuBar;

	auto sortMenu = new QMenu("Sortare");
	sortMenu->addAction(sortTitleAction);
	sortMenu->addAction(sortActorAction);
	sortMenu->addAction(sortYearGenreAction);

	menuBar->addMenu(sortMenu);
	menuBar->addAction(filterAction);
	menuBar->addAction(reportAction);
	menuBar->addAction(generateCartAction);

	mainLy->addWidget(menuBar);
	mainLy->addLayout(centerLy);

	movieList->setModel(model);
}

void AppGUI::_connect()
{

	// add
	QObject::connect(addButton, &QPushButton::clicked, [&]() {
		string title = titleData->text().toStdString();
		int year = yearData->currentText().toInt();
		string genre = genreData->currentText().toStdString();
		string actor = actorData->text().toStdString();
		try{
			srv.addMovie(title, genre, year, actor);
			loadData();
		}
		catch (Exception& err){
			QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
		}
		});


	// delete
	QObject::connect(deleteButton, &QPushButton::clicked, [&]() {
		try {
			srv.deleteMovie(currentMovie);
			loadData();
			currentMovie = -1;
		}
		catch(Exception & err)
		{
			QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
		}
		});

	// modify
	QObject::connect(modifyButton, &QPushButton::clicked, [&]() {
		
		string newTitle = titleData->text().toStdString();
		string newGenre = genreData->currentText().toStdString();
		int newYear = yearData->currentText().toInt();
		string newActor = actorData->text().toStdString();

		try {
			srv.updateMovie(currentMovie, newTitle, newGenre, newYear, newActor);
		}
		catch (Exception& err)
		{
			QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
		}
		});

	// exit
	QObject::connect(exitButton, &QPushButton::clicked, [&]() {
		if (sortWin.isVisible())
			sortWin.close();

		if (filterWin.isVisible())
			filterWin.close();

		close();
		});

	// undo 
	QObject::connect(undoButton, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			loadData();
		}
		catch (Exception& err) {
			QMessageBox::warning(nullptr, " ", QString::fromStdString(err.Message));
		}
		});

	/// --- sort actions ---

	// by title
	QObject::connect(sortTitleAction, &QAction::triggered, [&]() {
		sortWin.setLblText("Lista sortata dupa titlu");

		vector<Movie> sortedList = srv.sortMovies(1);

		sortWin.setMovieList(sortedList);

		sortWin.show();
		});

	// by actor
	QObject::connect(sortActorAction, &QAction::triggered, [&]() {
		sortWin.setLblText("Lista sortata dupa actor");

		vector<Movie> sortedList = srv.sortMovies(2);

		sortWin.setMovieList(sortedList);
		sortWin.show();
		});

	// by year and genre
	QObject::connect(sortYearGenreAction, &QAction::triggered, [&]() {
		sortWin.setLblText("Lista sortata dupa an si gen");

		vector<Movie> sortedList = srv.sortMovies(3);

		sortWin.setMovieList(sortedList);
		sortWin.show();
		});

	/// --- filter actions ---
	QObject::connect(filterAction, &QAction::triggered, [&]() {
		filterWin.show();
		});


	/// --- report ---
	QObject::connect(reportAction, &QAction::triggered, [&]() {
		ReportWindow*  reportWin = new ReportWindow(srv);
		reportWin->show();
		});


	// item selected from list
	/*
	QObject::connect(movieList, &QListWidget::itemClicked, [&]() {
		// set the currentMovie as the one that was clicked
		currentMovie = movieList->row(movieList->currentItem());

		titleData->setText(QString::fromStdString(srv.getMovie(currentMovie).get_title()));
		yearData->setCurrentText(QString::number(srv.getMovie(currentMovie).get_year()));
		genreData->setCurrentText(QString::fromStdString(srv.getMovie(currentMovie).get_genre()));
		actorData->setText(QString::fromStdString(srv.getMovie(currentMovie).get_actor()));

		});
		*/
	
	QObject::connect(movieList->selectionModel(), &QItemSelectionModel::selectionChanged, [this](const QItemSelection& selected) {
		
		if (selected.isEmpty())
		{
			titleData->setText(" ");
			actorData->setText(" ");
		}
		else {

			int index = selected.indexes().first().row();
			currentMovie = index;
			titleData->setText(QString::fromStdString(srv.getMovie(index).get_title()));
			yearData->setCurrentText(QString::number(srv.getMovie(index).get_year()));
			genreData->setCurrentText(QString::fromStdString(srv.getMovie(index).get_genre()));
			actorData->setText(QString::fromStdString(srv.getMovie(index).get_actor()));
		}
		});


	// cart
	QObject::connect(cartButton, &QPushButton::clicked, [&]() {
		CartWindow* cartWin = new CartWindow(srv.getCart());
		cartWin->show();
		});

	/// --- cart actions ---

	// add
	QObject::connect(addToCartButton, &QPushButton::clicked, [&]() {
		auto selection = movieList->selectionModel()->selectedIndexes();
		if (selection.isEmpty())
			QMessageBox::critical(nullptr, "Eroare", "Selectie invalida. Este necesar sa selectati un film");
		else {
			try {
				string title = titleData->text().toStdString();
				srv.addToCart(title);
			}
			catch (Exception& err)
			{
				QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
			}
		}
		});

	// empty
	QObject::connect(emptyCartButton, &QPushButton::clicked, [&]() {
		srv.emptyCart();
		});
	
	// generate
	QObject::connect(generateCartAction, &QAction::triggered, [&]() {
		QWidget* inputGenerateWin = new QWidget;

		auto numberToGenerateIn = new QSpinBox;
		//auto numberToGenerateIn = new QLineEdit;
		auto okButton = new QPushButton("&Ok");

		auto layout = new QFormLayout;

		auto mainLy = new QVBoxLayout;
		mainLy->addLayout(layout);
		mainLy->addWidget(okButton);

		inputGenerateWin->setLayout(mainLy);

		layout->addRow("Numar filme de generat", numberToGenerateIn);

		inputGenerateWin->show();

		

		QObject::connect(okButton, &QPushButton::clicked, [=]() {
			int numberToGenerate;
			numberToGenerate = numberToGenerateIn->value();
			
			//numberToGenerate = numberToGenerateIn->text().toInt();
			inputGenerateWin->close();

			try {
				srv.generateCart(numberToGenerate);
			}
			catch (Exception& err)
			{
				QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
			}

			});

		});

	QObject::connect(cartCrudGUIBttn, &QPushButton::clicked, [&]() {
		CosCRUDGUI* cartCG = new CosCRUDGUI(srv);
		cartCG->show();
		});

	QObject::connect(cartReadOnlyBttn, &QPushButton::clicked, [&]() {
		CosReadOnly* cartRdOnly = new CosReadOnly(srv.getCart());
		cartRdOnly->show();
		});
}

void AppGUI::loadData()
{
	model->setMovies(srv.getAll());
	/*
	movieList->clear();
	for (const auto& movie : srv.getAll())
	{
		QString currentTitle = QString::fromStdString(movie.get_title());
		movieList->addItem(currentTitle);
	}
	*/
}

AppGUI::~AppGUI()
{
	srv.getCart().removeObservers();
}
