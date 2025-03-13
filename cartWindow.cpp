#include "cartWindow.h"
#include <qlayout.h>
#include <qtimer.h>


CartWindow::CartWindow(Cart& cart) : crt{ cart } {
	initGUI();
	loadData();
	_connect_();
}

void CartWindow::initGUI()
{
	setStyleSheet("background-color: #63433E; color: white;");
	auto mainLy = new QVBoxLayout;
	setLayout(mainLy);

	//movieData->setStyleSheet("background-color: white; color: black;");
	mainLy->addWidget(movieData);
}

void CartWindow::loadData()
{

	movieData->clear();

	for (const auto& movie : crt.getAll())
	{
		QString movieInfo = "";
		movieInfo += QString::fromStdString(movie.get_title());
		movieInfo += " | ";
		movieInfo += QString::fromStdString(movie.get_genre());
		movieInfo += " | ";
		movieInfo += QString::number(movie.get_year());
		movieInfo += " | ";
		movieInfo += QString::fromStdString(movie.get_actor());

		movieData->addItem(movieInfo);
	}

}

void CartWindow::_connect_()
{
	crt.addObserver(this);

	/*
	QTimer* refreshTimer = new QTimer;
	QObject::connect(refreshTimer, &QTimer::timeout, [this]() {
		loadData();
		});
	refreshTimer->start(1000);
	*/
}

void CartWindow::update()
{
	loadData();
}
