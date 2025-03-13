#pragma once
#include <qtableview.h>
#include <qlistview.h>
#include <qdebug.h>
#include <vector>
using std::vector;

class MyModel : public QAbstractTableModel
{
public:
	MyModel(const vector<Movie>& mv) : movies{ mv }{}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return movies.size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	void setMovies(const vector<Movie>& mvs)
	{
		/*
		this->movies = mvs;
		QModelIndex topLeft = createIndex(0, 0);
		QModelIndex bottomRight = createIndex(movies.size(), movies.size());
		emit dataChanged(topLeft, bottomRight);
		*/
		beginResetModel();
		this->movies = mvs;
		endResetModel();
	}


	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole)
		{
			Movie mv = movies.at(index.row());
			if (index.column() == 0)
				return QString::fromStdString(mv.get_title()).arg(index.row() + 1).arg(1);
			if (index.column() == 1)
				return QString::fromStdString(mv.get_genre()).arg(index.row() + 1).arg(2);
			if (index.column() == 2)
				return QString::number(mv.get_year()).arg(index.row() + 1).arg(3);
			if (index.column() == 3)
				return QString::fromStdString(mv.get_actor()).arg(index.row() + 1).arg(4);
			
		}
		return QVariant{};
	}

private:

	vector<Movie> movies;
};