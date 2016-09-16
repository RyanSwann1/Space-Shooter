#include "Player.h"
#include "EntityManager.h"
#include "TextureManager.h"
#include "Direction.h"
#include "PlayerLaser.h"
#include "GameManager.h"
#include "GameRules.h"
#include "Utilities.h"
#include <assert.h>

Player* Player::m_localPlayer = nullptr;

Player::Player(EntityManager* entityManager)
	: Character(entityManager),
	m_weaponUpgrade(false),
	m_upgradedAmmoCount(0)
{
	m_localPlayer = this;
	m_size = sf::Vector2f(.5f, .5f);
	m_name = "Player";
	m_entityType = EntityType::Player;
	m_speed = sf::Vector2f(10, 10);
	m_onCollisionDamage = 1;
	m_maxLives = 3;
	Entity::applyTexture(); //Apply texture to entity
	m_audioPlayer.addAudioClip(std::string("PlayerLaser"), new Audio(*m_entityManager->getSharedContext()->m_soundManager, std::string("PlayerLaser")));
	m_audioPlayer.addAudioClip(std::string("PickUpPowerUp"), new Audio(*m_entityManager->getSharedContext()->m_soundManager, std::string("PickUpPowerUp")));
	m_audioPlayer.addAudioClip(std::string("PlayerHit"), new Audio(*m_entityManager->getSharedContext()->m_soundManager, std::string("PlayerHit")));
	//Entity::applySound(); //Apply sound to entity
	m_direction = Direction::None;
	reset();
	m_gameWinningScore = GameRules::GAME_WINNING_SCORE;
	
	Observer* gameManager = new GameManager(m_entityManager->getSharedContext());
	if (!m_communicator.hasObserver(gameManager))
	{
		m_communicator.addObserver(gameManager);
	}

	//Cannot allow more than one callback at teh same time
	EventSystem* eventSystem = m_entityManager->getSharedContext()->m_eventSystem;
	eventSystem->addCallback<Player>(StateType::Game, "Move_Left", &Player::reactToInput, this);
	eventSystem->addCallback<Player>(StateType::Game, "Move_Right", &Player::reactToInput, this);
	eventSystem->addCallback<Player>(StateType::Game, "Move_Up", &Player::reactToInput, this);
	eventSystem->addCallback<Player>(StateType::Game, "Move_Down", &Player::reactToInput, this);
	eventSystem->addCallback<Player>(StateType::Game, "Fire_Laser", &Player::reactToInput, this);

	initializeUI();
}

Player::~Player()
{
	EventSystem* eventSystem = m_entityManager->getSharedContext()->m_eventSystem;
	eventSystem->removeCallback(StateType::Game, "Move_Left");
	eventSystem->removeCallback(StateType::Game, "Move_Right");
	eventSystem->removeCallback(StateType::Game, "Move_Up");
	eventSystem->removeCallback(StateType::Game, "Move_Down");
	eventSystem->removeCallback(StateType::Game, "Fire_Laser");

	m_localPlayer = nullptr;
	m_audioPlayer.purgeAudioClips();
}

void Player::update(const float deltaTime)
{
	m_timeElasped += deltaTime;
	Entity::update(deltaTime);

	//Check boundary
	sf::Vector2u mapBoundary = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.x < 0) {
		m_position.x = 0;
	}
	else if ((m_position.x + m_size.x) >= mapBoundary.x) {
		m_position.x = mapBoundary.x;
	}

	else if (m_position.y > mapBoundary.y / 2.0f) {
		m_position.y = mapBoundary.y / 2.0f;
	}

	else if (m_position.y < 0) {
		m_position.y = 0;
	}

	//Check players lives
	if (m_lives <= 0)
	{
		m_communicator.notify(*this, GameEvent::Player_Dead);
		//reset();
	}

	//Check for game winning score
	if (m_score >= m_gameWinningScore)
	{
		m_communicator.notify(*this, GameEvent::Game_Won);
	}
}

void Player::addUpgradedAmmoCount(const unsigned int i)
{
	m_upgradedAmmoCount += i;
	m_audioPlayer.playAudioClip(std::string("PickUpPowerUp"));
}

void Player::addScore(const int i)
{
	m_score += i;
	m_entityManager->getSharedContext()->m_gui->updateEntry("ScoreText", std::string("Score: " + std::to_string(m_score)));
	std::cout << "\n" << std::to_string(m_score) << "\n";
	std::cout << m_score << "\n";
}

void Player::reduceLivesAmount(const int i)
{
	Character::reduceLivesAmount(i);
	GUI* gui = m_entityManager->getSharedContext()->m_gui;
	gui->updateEntry(std::string("LivesText"), std::string("Lives: " + std::to_string(m_lives)));
	m_audioPlayer.playAudioClip(std::string("PlayerHit"));
}

void Player::addLivesAmount(const int i)
{
	Character::addLivesAmount(i);
	GUI* gui = m_entityManager->getSharedContext()->m_gui;
	gui->updateEntry(std::string("LivesText"), std::string("Lives: " + std::to_string(m_lives)));
	m_audioPlayer.playAudioClip(std::string("PickUpPowerUp"));
}

void Player::reactToInput(EventDetails* eventDetails)
{
	if (eventDetails->m_name == "Move_Left") {
		move(Direction::Left);
	}
	else if (eventDetails->m_name == "Move_Right") {
		move(Direction::Right);
	}
	else if (eventDetails->m_name == "Move_Up") {
		move(Direction::Up);
	}
	else if (eventDetails->m_name == "Move_Down") {
		move(Direction::Down);
	}
	else if (eventDetails->m_name == "Fire_Laser") {
		fireLaser();
	}
}

void Player::fireLaser()
{
	if (m_timeElasped >= m_nextFireTime)
	{
		//Play fire sound
		m_audioPlayer.playAudioClip(std::string("PlayerLaser"));

		if (m_upgradedAmmoCount <= 0)
		{
			Entity* projectile = new PlayerLaser(m_entityManager);
			projectile->setStartPos(getFirePos());
			m_entityManager->addEntity(EntityType::PlayerProjectile, projectile);
		}
		else
		{
			m_upgradedAmmoCount -= 2;
			Entity* projectile1 = new PlayerLaser(m_entityManager);
			Entity* projectile2 = new PlayerLaser(m_entityManager);
			projectile1->setStartPos(sf::Vector2f(m_position.x - 25, m_position.y));
			projectile2->setStartPos(sf::Vector2f(m_position.x + 25, m_position.y));
			m_entityManager->addEntity(EntityType::PlayerProjectile, projectile1);
			m_entityManager->addEntity(EntityType::PlayerProjectile, projectile2);
		}
		m_nextFireTime += m_timeBetweenFire;
	}
}

void Player::initializeUI()
{
	GUI* gui = m_entityManager->getSharedContext()->m_gui;
	FontManager* fontManager = m_entityManager->getSharedContext()->m_fontManager;

	gui->addEntry("LivesText", new GUIEntry(fontManager, std::string("Lives: " + std::to_string(m_lives)), sf::Vector2f(25, 25), Utilities::getFontName(), Utilities::getDefaultFontSize()));
	gui->addEntry("ScoreText", new GUIEntry(fontManager, std::string("Score: " + std::to_string(m_score)), sf::Vector2f(375, 25), Utilities::getFontName(), Utilities::getDefaultFontSize()));


	////Set up UI
	//sf::Text scoreText;
	////scoreText.setString(sf::String("Score: " + std::to_string(m_score)));
	//scoreText.setString(sf::String("Score: "));
	//scoreText.setCharacterSize(12);
	////sf::Text livesText;
	////livesText.setString(sf::String("Lives: " + std::to_string(m_lives)));

	//GUIEntry scoreGUI(m_entityManager->getSharedContext()->m_fontManager, scoreText, sf::Vector2f(420, 550), "SPACEMAN");
	////GUIEntry livesGUI(m_entityManager->getSharedContext()->m_fontManager, livesText, sf::Vector2f(25, 650), "SPACEMAN");
	////GUIEntry livesGUI(m_entityManager)
	//GUI* gui = m_entityManager->getSharedContext()->m_gui;
	//gui->addEntry("ScoreText", &scoreGUI);
	////gui->addEntry("LivesText", &livesGUI);
}

void Player::reset()
{
	m_score = 0;
	m_lives = m_maxLives;
	m_position = sf::Vector2f(225, 200);
	m_timeBetweenFire = .75f;
	m_nextFireTime = 0;
	m_timeElasped = 0;
}