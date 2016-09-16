#include "PowerUpWeapon.h"
#include "EntityManager.h"
#include "Player.h"
#include "Utilities.h"

PowerUpWeapon::PowerUpWeapon(EntityManager* entityManager)
	:PowerUp(entityManager)
{
	m_name = "Power_Up_Weapon";
	m_direction = Direction::Up;
	m_entityType = EntityType::PowerUpProjectile;
	m_speed = sf::Vector2f(0, 0.030f);
	m_size = sf::Vector2f(1, 1);
	m_position = sf::Vector2f(Utilities::getRandomNumber(25, 625), 680);
	m_powerUpValue = 10;
	Entity::applyTexture();
}


PowerUpWeapon::~PowerUpWeapon()
{
}

void PowerUpWeapon::onEntityCollision(Entity * collider)
{
	if (collider->getType() == EntityType::Player)
	{
		Player* player = (Player*)collider;
		player->addUpgradedAmmoCount(m_powerUpValue);
	}

	m_entityManager->removeEntity(m_ID);
}

void PowerUpWeapon::update(const float deltaTime)
{
	PowerUp::move(m_direction);
	Entity::update(deltaTime);

	sf::Vector2u mapSize = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y <= 0)
	{
		m_entityManager->removeEntity(m_ID);
	}
}
