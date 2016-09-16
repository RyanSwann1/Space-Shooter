#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "EventSystem.h"
#include "SharedContext.h"
#include "StateType.h"
#include "StateBase.h"
#include <SFML\Window.hpp>
#include <unordered_map>
#include <functional>
#include <vector>

class StateManager
{
public:
	StateManager(SharedContext* sharedContext);
	~StateManager();
	
	StateType getStateCurrent() const { return m_stateCurrent; }

	void switchTo(const StateType state);
	void remove(const StateType state) { m_statesToRemove.push_back(state); }
	//Remove particular state once manager has finished iterating over them.
	void processRequests(); 

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);

	SharedContext* getSharedContext() { return m_sharedContext; }
	size_t getStateSize() const { return m_states.size(); }

private:
	std::unordered_map<StateType, std::function<StateBase*()>> m_stateFactory;
	std::vector<std::pair<StateType, StateBase*>> m_states;
	std::vector<StateType> m_statesToRemove;
	SharedContext* m_sharedContext;
	StateType m_stateCurrent;

	template <class T>
	void registerState(const StateType type)
	{
		if (m_stateFactory.find(type) == m_stateFactory.cend()) 
		{
			m_stateFactory[type] = [this]() -> StateBase*
			{
				return new T(this);
			};
		}
	}

	void createState(const StateType state);
	void removeState(const StateType state);
	void purgeStates();
};
#endif // !STATE_MANAGER_H