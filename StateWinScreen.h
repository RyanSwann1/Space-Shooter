#pragma once
#include "StateBase.h"
#include <SFML\Graphics.hpp>
struct EventDetails;
class StateWinScreen :
	public StateBase
{
public:
	StateWinScreen(StateManager* stateManager);
	~StateWinScreen();

	void onCreate() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	void reactToInput(EventDetails* eventDetails);
	void initializeUI();

};

