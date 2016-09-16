#include "Communicator.h"



Communicator::Communicator()
{
}

Communicator::~Communicator()
{
	purge();
}

bool Communicator::hasObserver(Observer * observer)
{
	for (auto &i : m_observers)
	{
		if (i == observer)
		{
			return true;
		}
	}
	return false;
}

void Communicator::removeObserver(Observer * observer)
{
	for (auto iter = m_observers.begin(); iter != m_observers.end();)
	{
		if (*iter == observer)
		{
			delete *iter;
			*iter = nullptr;
			iter = m_observers.erase(iter);
			return;
		}
		else
		{
			iter++;
		}
	}
}

void Communicator::notify(Entity& entity, const GameEvent event)
{
	for (auto &i : m_observers)
	{
		i->onNotify(entity, event);
	}
}

void Communicator::purge()
{
	for (auto &i : m_observers)
	{
		delete i;
		i = nullptr;
	}
	m_observers.clear();
}
