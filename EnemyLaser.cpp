#include "EnemyLaser.h"
#include "EntityManager.h"
#include "Character.h"
#include "Player.h"

EnemyLaser::EnemyLaser(EntityManager* entityManager)
	: Projectile(entityManager)
{
	m_direction = Direction::Up;
	m_size = sf::Vector2f(.75f, .75f);
	m_entityType = EntityType::EnemyProjectile;
	m_name = "Enemy_Laser";
	m_speed = sf::Vector2f(0, .030f);
	m_onCollisionDamage = 1;
	Entity::applyTexture();
}

EnemyLaser::~EnemyLaser()
{
}

void EnemyLaser::onEntityCollision(Entity * collider)
{
	if (collider->getType() == EntityType::Player)
	{
		Player* player = Player::getLocalPlayer();
		player->reduceLivesAmount(m_onCollisionDamage);
	}

	m_entityManager->removeEntity(m_ID);
}

void EnemyLaser::update(const float deltaTime)
{
	Projectile::move(m_direction);
	Entity::update(deltaTime);

	sf::Vector2u mapSize = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y <= -15)
	{
		m_entityManager->removeEntity(m_ID);
	}
}

