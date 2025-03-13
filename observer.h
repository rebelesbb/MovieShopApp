#pragma once

#include <vector>
#include <algorithm>
#include <qdebug.h>

class Observer {
public:
	virtual void update() = 0;
};


class Observable {
public:
	void addObserver(Observer* obs) {
		observers.push_back(obs);
	}

	void removeObservers()
	{
		observers.erase(observers.begin(), observers.end());
	}
protected:
	std::vector<Observer*> observers;
	void notify() {
		for (auto obs : observers)
		{
			obs->update();
		}
	}
};