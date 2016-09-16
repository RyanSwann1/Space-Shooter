#ifndef STATE_GAME_H
#define STATE_GAME_H

#include "Player.h"
#include "StateBase.h"
#include "Spawner.h"
#include "GameManager.h"
#include <SFML\Audio.hpp>
#include <vector>

class StateGame :
	public StateBase
{
public:
	StateGame(StateManager* stateManager);
	~StateGame();

	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	
private:
	float m_timeElasped;
	std::vector<Spawner*> m_spawners; //Contains everything that will spawn in game
	bool m_gamePaused;
	void reactToInput(EventDetails* eventDetails);

	sf::Text m_pausedText;
	sf::Font m_font;
};
#endif // !STATE_GAME_H
