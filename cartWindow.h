#pragma once
#include <qwidget.h>
#include "observer.h"
#include "cart.h"
#include <qlistwidget.h>

class CartWindow : public QWidget, public Observer
{
public:
	CartWindow(Cart& cart);

private:
	Cart& crt;
	QListWidget* movieData = new QListWidget;
	int count;

	void initGUI();
	void loadData();
	void _connect_();
	void update() override;
};