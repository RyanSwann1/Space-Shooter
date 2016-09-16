#ifndef STATE_BASE_H
#define STATE_BASE_H

#include "SFML\Graphics.hpp"

class StateManager;
class StateBase
{

public:
	StateBase(StateManager* stateManager)
		:m_stateManager(stateManager) {}
	virtual ~StateBase() {}

	virtual void onCreate() {}
	virtual void onDestroy() {}

	virtual void onEnter() {}
	virtual void onExit() {}

	virtual void update(const float deltaTime) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;

protected:
	StateManager* m_stateManager;
};
#endif // !STATE_BASE_H
