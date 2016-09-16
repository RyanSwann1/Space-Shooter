#pragma once

#include "Observer.h"
#include <vector>

class Communicator
{
public:
	Communicator();
	~Communicator();

	void addObserver(Observer* observer) { m_observers.emplace_back(observer); }
	bool hasObserver(Observer* observer);
	void removeObserver(Observer* observer);
	void notify(Entity& entity, const GameEvent event);

private:
	std::vector<Observer*> m_observers;

	void purge();
};

