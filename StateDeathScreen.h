#pragma once
#include "StateBase.h"
#include <SFML\Graphics.hpp>
#include <string>
struct EventDetails;
class StateManager;
class StateDeathScreen :
	public StateBase
{
public:
	StateDeathScreen(StateManager* stateManager);
	~StateDeathScreen();

	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	void reactToInput(EventDetails* eventDetails);
	void initializeUI();
};

