#include "cartReadOnly.h"
#include <qlayout.h>
#include <vector>
#include <qpainter.h>

CosReadOnly::CosReadOnly(Cart& crt) : crt{ crt }
{
	setStyleSheet("background-color: #63433E; color: white;");
	crt.addObserver(this);
}

void CosReadOnly::paintEvent(QPaintEvent* ev)
{
	QPainter p{ this };
	int x = 10, y = 30;

	for (const auto& m : crt.getAll())
	{
		if (m.get_genre() == "Horror")
		{
			QRectF rect(x, y, 100, 100);
			p.drawPie(rect, 16 * 30, 120 * 16);
		}
		else if (m.get_genre() == "Actiune")
		{
			QRectF rect(x, y, 100, 100);
			p.drawChord(rect, 16 * 30, 120 * 16);
		}
		else if (m.get_genre() == "Comedie")
		{
			p.drawEllipse(x, y, 60, 80);
		}
		else if (m.get_genre() == "Romance")
		{
			p.drawRect(x, y, 60, 80);
		}
		else {
			QPointF points[5] = {
				QPointF(x,y),
				QPointF(x, y + 60),
				QPointF(x + 60, y),
				QPointF(x + 60, y + 90),
				QPointF(x + 90, y + 70)
			};
			p.drawConvexPolygon(points, 5);
		}
		x += 120;
		if (x == 490) x = 10, y += 100;
			 
	}


}

void CosReadOnly::update()
{
	repaint();
}
