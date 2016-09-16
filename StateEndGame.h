#pragma once
#include "StateBase.h"
class StateEndGame :
	public StateBase
{
public:
	StateEndGame(StateManager* stateManager);
	~StateEndGame();

	void onEnter();

	void update(const float deltaTime) override {}
	void draw(sf::RenderWindow& window) override {}

private:

};

