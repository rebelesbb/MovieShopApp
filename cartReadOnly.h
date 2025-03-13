#pragma once
#include "cart.h"
#include <qwidget.h>
#include <qpaintdevice.h>


class CosReadOnly : public QWidget, public Observer
{
public:
	CosReadOnly(Cart& crt);

private:
	Cart& crt;

	void paintEvent(QPaintEvent* ev) override;
	void update() override;
};