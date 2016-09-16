#include "Entity.h"
#include "EntityManager.h"
#include <cmath>


Entity::Entity(EntityManager* entityManager)
	: m_entityManager(entityManager),
	m_ID(0),
	m_texture(nullptr)
{

}

Entity::~Entity()
{
	m_entityManager->getSharedContext()->m_textureManager->unloadResource(m_name);
}

void Entity::draw(sf::RenderWindow & window)
{
	m_sprite.setPosition(m_position.x, m_position.y);
	m_sprite.setScale(m_size.x, m_size.y);
	window.draw(m_sprite);
	//drawAABB(window);
}

void Entity::update(const float deltaTime)
{
	move(); //Move the entity

	updateAABB(); //Update the bounding box
}

void Entity::move()
{
	m_oldPosition = m_position; //Assign the old position
	m_position += sf::Vector2f(m_velocity.x, m_velocity.y);
	m_velocity = sf::Vector2f(0, 0);
}

void Entity::updateAABB()
{
	m_AABB = sf::FloatRect(m_position.x - (m_texture->getSize().x / 3.0f), m_position.y - (m_texture->getSize().y / 3.0f), m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
}

void Entity::applyTexture()
{
	TextureManager* textureManager = m_entityManager->getSharedContext()->m_textureManager;
	if (textureManager->requireResource(m_name))
	{
		m_texture = textureManager->getResource(m_name);
		m_sprite.setTexture(*m_texture);
		//m_sprite.setTexture(*textureManager->getResource(m_name));
		m_sprite.setOrigin(m_texture->getSize().x / 2.0f, m_texture->getSize().y / 2.0f);
	}
}

void Entity::drawAABB(sf::RenderWindow& window)
{
	sf::RectangleShape rect;
	rect.setPosition(sf::Vector2f(m_AABB.left, m_AABB.top));
	rect.setSize(sf::Vector2f(m_AABB.width, m_AABB.height));
	rect.setFillColor(sf::Color::Green);
	window.draw(rect);
}