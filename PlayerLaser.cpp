#include "PlayerLaser.h"
#include "EntityManager.h"
#include "Character.h"

PlayerLaser::PlayerLaser(EntityManager* entityManager)
	:Projectile(entityManager)
{
	m_name = "Player_Laser";
	m_size = sf::Vector2f(.75f, .75f);
	m_speed = sf::Vector2f(0, .1);
	m_onCollisionDamage = 1;
	m_direction = Direction::Down;
	m_entityType = EntityType::PlayerProjectile;
	Entity::applyTexture();
}

PlayerLaser::~PlayerLaser()
{
}

void PlayerLaser::update(const float deltaTime)
{
	//Control movement
	Projectile::move(m_direction);
	Entity::update(deltaTime);
	

	//Control boundaries 
	sf::Vector2u mapSize = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y >= mapSize.y)
	{
		m_entityManager->removeEntity(m_ID);
	}	
}

void PlayerLaser::onEntityCollision(Entity * collider)
{
	//Cannot collide with self
	if (collider->getType() == EntityType::Player)
	{
		return;
	}

	if (collider->getType() == EntityType::Enemy)
	{
		Character* enemy = (Character*)collider;
		enemy->reduceLivesAmount(m_onCollisionDamage);
	}
	
	m_entityManager->removeEntity(m_ID);
}
