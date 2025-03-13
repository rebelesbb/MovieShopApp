#include "CartCrudGUI.h"
#include <qlayout.h>
#include <qmessagebox.h>
#include <qtableview.h>

CosCRUDGUI::CosCRUDGUI(MovieService& srv) : srv{ srv } {
	initGUI();
	_connect_();
	loadData();
}

void CosCRUDGUI::initGUI()
{
	movieTable->setModel(model);

	auto mainLy = new QHBoxLayout;
	setLayout(mainLy);

	setStyleSheet("background-color: #63433E; color: white;");

	mainLy->addWidget(movieTable);

	QStringList headers;
	headers << "Titlu" << "Gen" << "An" << "Actor";

	auto interactiveSideLy = new QVBoxLayout;

	generateValue->setMinimum(1);

	interactiveSideLy->addWidget(generateValue);
	interactiveSideLy->addWidget(emptyBttn);
	interactiveSideLy->addWidget(generateBttn);

	mainLy->addLayout(interactiveSideLy);

}

void CosCRUDGUI::_connect_()
{
	srv.getCart().addObserver(this);

	QObject::connect(emptyBttn, &QPushButton::clicked, [&]() {
		srv.emptyCart();
		});

	QObject::connect(generateBttn, &QPushButton::clicked, [&]() {
		int valueToGenerate = generateValue->value();
		try {
			srv.generateCart(valueToGenerate);
		}
		catch (Exception& err)
		{
			QMessageBox::critical(nullptr, "Eroare", QString::fromStdString(err.Message));
		}
		});


}

void CosCRUDGUI::loadData()
{
	model->setMovies(srv.getAllCart());
	/*
	model->setColumnCount(4);
	model->setRowCount(srv.getCartSize());

	int index = 0;

	for (const auto& m : srv.getAllCart())
	{
		QTableWidgetItem* movieTitle = new QTableWidgetItem{ QString::fromStdString(m.get_title()) };
		QTableWidgetItem* movieGenre = new QTableWidgetItem{ QString::fromStdString(m.get_genre()) };
		QTableWidgetItem* movieYear = new QTableWidgetItem{ QString::number(m.get_year())};
		QTableWidgetItem* movieActor = new QTableWidgetItem{ QString::fromStdString(m.get_actor()) };

		movieTable->setItem(index, 0, movieTitle);
		movieTable->setItem(index, 1, movieGenre);
		movieTable->setItem(index, 2, movieYear);
		movieTable->setItem(index, 3, movieActor);

		index++;
	}
	*/
}

void CosCRUDGUI::update()
{
	loadData();
}
