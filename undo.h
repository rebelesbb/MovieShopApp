#pragma once
#include "movie_repo.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() = default;
};


class UndoAdd : public UndoAction {

private:
	Repo& repo;

public:

	UndoAdd(Repo& repository) : repo{ repository } {}

	void doUndo() override {
		repo.delete_(repo.size()-1);
	}
};

class UndoDelete : public UndoAction {

private:
	Movie deletedMovie;
	Repo& repo;
	int positionDeleted;

public:

	UndoDelete(Repo& repo, const Movie& movie, int position) : repo{ repo }, deletedMovie{ movie }, positionDeleted{ position } {}

	void doUndo() override {
		repo.insert(positionDeleted, deletedMovie);
	}

};

class UndoModify : public UndoAction {

private:
	Movie modifiedMovie;
	Repo& repo;
	int positionModified;

public:
	UndoModify(Repo& repo, const Movie& movie, int position) : repo{ repo }, modifiedMovie{ movie }, positionModified{ position } {}

	void doUndo() override {
		repo.modify(positionModified, modifiedMovie);
	}
};
