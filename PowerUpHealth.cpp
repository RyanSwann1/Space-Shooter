#include "PowerUpHealth.h"
#include "EntityManager.h"
#include "Character.h"
#include "Utilities.h"

PowerUpHealth::PowerUpHealth(EntityManager* entityManager)
	:PowerUp(entityManager)
{
	m_name = "Power_Up_Health";
	m_entityType = EntityType::PowerUpHealth;
	m_direction = Direction::Up;
	m_speed = sf::Vector2f(0, 0.010f);
	m_size = sf::Vector2f(1, 1);
	m_position = sf::Vector2f(Utilities::getRandomNumber(25, 625), 680);
	m_powerUpValue = 1;
	Entity::applyTexture();
}

PowerUpHealth::~PowerUpHealth()
{
}

void PowerUpHealth::onEntityCollision(Entity * collider)
{
	if (collider->getType() == EntityType::Player)
	{
		Character* character = (Character*)collider;
		character->addLivesAmount(m_powerUpValue);
	}

	m_entityManager->removeEntity(m_ID);
	
}

void PowerUpHealth::update(const float deltaTime)
{
	PowerUp::move(m_direction);
	Entity::update(deltaTime);

	sf::Vector2u mapBoundary = m_entityManager->getSharedContext()->m_window->getSize();
	if (m_position.y <= 0)
	{
		m_entityManager->removeEntity(m_ID);
	}
}
