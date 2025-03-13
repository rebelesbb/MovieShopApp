#pragma once
#include "observer.h"
#include <qwidget.h>
#include "movie_service.h"
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qspinbox.h>
#include <qtableview.h>
#include "myModel.h"

class CosCRUDGUI : public QWidget, public Observer
{
public:
	CosCRUDGUI(MovieService& srv);

private:
	void initGUI();
	void _connect_();
	void loadData();

	void update() override;

	MovieService& srv;
	MyModel* model = new MyModel{srv.getAllCart()};
	QTableView* movieTable = new QTableView;

	QPushButton* emptyBttn = new QPushButton("&Golire");
	QPushButton* generateBttn = new QPushButton("&Generare");

	//QTableWidget* movieTable = new QTableWidget(0,4,this);

	QSpinBox* generateValue = new QSpinBox;
};