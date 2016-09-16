#pragma once
#include "StateBase.h"
#include "AudioPlayer.h"
#include <SFML\Graphics.hpp>
#include <string>
struct EventDetails;
class StateMainMenu :
	public StateBase
{
public:
	StateMainMenu(StateManager* stateManager);
	~StateMainMenu();

	void onCreate() override;
	void onDestroy() override;

	void draw(sf::RenderWindow& window) override {}
	void update(const float deltaTime) override {}

private:
	void reactToInput(EventDetails* eventDetails);
	void initializeUI();
	AudioPlayer m_audioPlayer;
};

