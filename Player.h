#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "Communicator.h"
#include "GUI.h"
#include <SFML\Graphics.hpp>

#include <vector>
struct EventDetails;
class Player :
	public Character, public Communicator
{
public:
	Player(EntityManager* entityManager);
	~Player();

	void onEntityCollision(Entity* collider) override {}
	void update(const float deltaTime) override;
	void addUpgradedAmmoCount(const unsigned int i);
	void addScore(const int i);
	void reduceLivesAmount(const int i) override;
	void addLivesAmount(const int i) override;
	static Player* getLocalPlayer() { return m_localPlayer; }

private:
	void reactToInput(EventDetails* eventDetails);
	void fireLaser();
	bool m_weaponUpgrade;
	int m_upgradedAmmoCount;
	int m_score;
	int m_gameWinningScore;
	Communicator m_communicator;
	//Questionable UI code
	GUI m_gui;
	static Player* m_localPlayer;

	void initializeUI();
	inline sf::Vector2f getFirePos() const { return sf::Vector2f(m_position.x, m_position.y); }
	void reset();
};
#endif // !PLAYER_H
