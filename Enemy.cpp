#include "Enemy.h"
#include "EntityManager.h"
#include "EnemyLaser.h"
#include "Player.h"

Enemy::Enemy(EntityManager* entityManager)
	: Character(entityManager)
{
	m_name = "Enemy";
	m_speed = sf::Vector2f(.025f, .010f);
	m_direction = Direction::Up;
	m_entityType = EntityType::Enemy;
	m_size = sf::Vector2f(.5f, .5f);
	m_lives = 1;
	m_onCollisionDamage = 1;
	m_onDestroyPoint = 1;
	m_nextFireTime = 0.75f;
	m_timeBetweenFire = 3.5f;
	m_timeElasped = 0;
	Entity::applyTexture();
	m_audioPlayer.addAudioClip(std::string("EnemyLaser"), new Audio(*m_entityManager->getSharedContext()->m_soundManager, std::string("EnemyLaser")));
	m_audioPlayer.addAudioClip(std::string("EnemyExplosion"), new Audio(*m_entityManager->getSharedContext()->m_soundManager, std::string("EnemyExplosion")));
}

Enemy::~Enemy()
{
	m_audioPlayer.purgeAudioClips();
}

void Enemy::onEntityCollision(Entity * collision)
{
	if (collision->getType() == EntityType::PlayerProjectile)
	{
		Player* player = Player::getLocalPlayer();
		player->addScore(m_onDestroyPoint);
		std::cout << "Occured" << "\n";

		reduceLivesAmount(collision->getDamage());
	}
	else if (collision->getType() == EntityType::Player)
	{
		Player* player = Player::getLocalPlayer();
		player->reduceLivesAmount(m_onCollisionDamage);
		m_entityManager->removeEntity(m_ID);
	}
	else
	{
		m_entityManager->removeEntity(m_ID);
	}
}

void Enemy::update(const float deltaTime)
{
	m_timeElasped += deltaTime;
	Character::move(m_direction);
	Entity::update(deltaTime);

	sf::Vector2u mapSize = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y <= 0)
	{
		m_entityManager->removeEntity(m_ID);
	}
	
	if (m_timeElasped >= m_nextFireTime)
	{
		fireProjectile();
		m_nextFireTime += m_timeBetweenFire;
		m_audioPlayer.playAudioClip(std::string("EnemyLaser"));
	}
}

void Enemy::reduceLivesAmount(const int i)
{
	Character::reduceLivesAmount(i);
	if (m_lives <= 0)
	{
		m_audioPlayer.playAudioClip(std::string("EnemyExplosion"));
		m_entityManager->removeEntity(m_ID);
	}
}

void Enemy::fireProjectile()
{
	Entity* projectile = new EnemyLaser(m_entityManager);
	projectile->setStartPos(getFirePos());
	m_entityManager->addEntity(EntityType::EnemyProjectile, projectile);
}