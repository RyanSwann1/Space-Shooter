#include "StateManager.h"
#include "StateMainMenu.h"
#include "StateGame.h"
#include "StateWinScreen.h"
#include "StateDeathScreen.h"
#include "StateEndGame.h"
#include <iostream>

StateManager::StateManager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext)
{
	registerState<StateMainMenu>(StateType::MainMenu);
	registerState<StateGame>(StateType::Game);
	registerState<StateDeathScreen>(StateType::DeathScreen);
	registerState<StateWinScreen>(StateType::WinScreen);
	registerState<StateEndGame>(StateType::EndGame);
}

StateManager::~StateManager()
{
	purgeStates();
}

void StateManager::switchTo(const StateType state)
{
	//size_t size = 1;
	//if (m_states.size() > size)
	//{
	//	for (auto cIter = m_states.cbegin(); cIter != m_states.cend(); cIter++)
	//	{
	//		if(cIter->first == state)
	//		{
	//			//Upon reallocation of the container, iterators are invalidate
	//			//Exit the current state
	//			cIter->second->onExit(); 
	//			StateType tempType = cIter->first;
	//			StateBase* tempState = cIter->second;
	//			//Enter the new state
	//			//Remove old position of newly transferred state
	//			m_states.erase(cIter);
	//			m_states.emplace_back(tempType, tempState);
	//			m_states.back().second->onEnter();
	//			return; 
	//		}
	//	}
	//}

	createState(state);
}

void StateManager::createState(const StateType state)
{
	auto iter = m_stateFactory.find(state);
	if (iter != m_stateFactory.cend())
	{
		m_states.emplace_back(iter->first, iter->second());

		m_states.back().second->onCreate();
		m_states.back().second->onEnter();
		m_stateCurrent = m_states.back().first;
	}
}

void StateManager::removeState(const StateType state)
{
	for (auto iter = m_states.begin(); iter != m_states.end(); iter++)
	{
		if (iter->first == state)
		{
			iter->second->onExit();
			iter->second->onDestroy();
			//delete iter->second;
			//iter->second = nullptr;
			m_states.erase(iter); 
			std::cout << "\n" << "Size of states: " << m_states.size() << "\n";
			return;
		}
		
	}
}

void StateManager::purgeStates()
{
	for (auto &i : m_states)
	{
		i.second->onDestroy();
		delete i.second;
	}
	m_states.clear();
}

void StateManager::processRequests()
{
	while (m_statesToRemove.begin() != m_statesToRemove.end())
	{
		removeState(m_statesToRemove.back());
		m_statesToRemove.pop_back();
	}
}

void StateManager::update(const float deltaTime)
{
	m_states.back().second->update(deltaTime);
}

void StateManager::draw(sf::RenderWindow & window)
{
	m_states.back().second->draw(window);
}
