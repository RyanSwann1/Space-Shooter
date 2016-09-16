#include "EntityManager.h"
#include "SharedContext.h"
#include "Player.h"
#include "PlayerLaser.h"
#include "Enemy.h"
#include "EnemyLaser.h"
#include "PowerUpHealth.h"
#include "PowerUpWeapon.h"

EntityManager::EntityManager(SharedContext* sharedContext)
	: m_sharedContext(sharedContext),
	m_entityCount(0)
{
	registerEntity<Player>(EntityType::Player);
	registerEntity<PlayerLaser>(EntityType::PlayerProjectile);
	registerEntity<Enemy>(EntityType::Enemy);
	registerEntity<EnemyLaser>(EntityType::EnemyProjectile);
	registerEntity<PowerUpHealth>(EntityType::PowerUpHealth);
	registerEntity<PowerUpWeapon>(EntityType::PowerUpProjectile);
}

EntityManager::~EntityManager()
{
	purgeEntities();
	for (auto &i : m_entityFactory)
	{
		delete i.second();
		i.second = nullptr;
	}
	m_entityFactory.clear();
	m_entitiesToRemove.clear();
}

void EntityManager::addEntity(const EntityType type)
{
	auto iter = m_entityFactory.find(type);
	if (iter != m_entityFactory.cend())
	{
		m_entityCount++; //Increase entity count for each entity added
		m_entities.emplace_back(iter->second(), m_entityCount);
		m_entities.back().first->setID(m_entityCount); //Set ID for the entity
		std::cout << "\n" << "Entity count: " << m_entityCount << "\n";
	}
	else {
		std::cerr << "Couldn't find Entity " << "\n";
	}
}

void EntityManager::addEntity(const EntityType type, Entity * entity)
{
	if (m_entityFactory.find(type) != m_entityFactory.cend())
	{
		m_entityCount++;
		m_entities.emplace_back(entity, m_entityCount);
		m_entities.back().first->setID(m_entityCount);
		std::cout << "\n" << "Entity count: " << m_entityCount << "\n";
	}
	else {
		std::cerr << "Couldn't find entity." << "\n";
	}
}

void EntityManager::removeEntity(const unsigned int id)
{
	//Make sure the requested entity to add is not already added
	bool removeEntity = true;
	for (auto cIter = m_entitiesToRemove.cbegin(); cIter != m_entitiesToRemove.cend(); cIter++)
	{
		if (*cIter == id) {
			removeEntity = false;
		}
	}

	if (removeEntity) {
		m_entitiesToRemove.push_back(id);
	}
}

void EntityManager::processRemovals()
{
	while (m_entitiesToRemove.begin() != m_entitiesToRemove.end())
	{
		if (removeActiveEntity(m_entitiesToRemove.back()))
		{
			m_entitiesToRemove.pop_back();
		}
		else
		{
			std::cout << "Entity not found to delete.\n";
		}
	}
}

void EntityManager::update(const float deltaTime)
{
	auto entitiesCopy = m_entities;
	for (auto &i : entitiesCopy)
	{
		i.first->update(deltaTime);
	}

	checkCollisions();
	processRemovals();
}

void EntityManager::draw(sf::RenderWindow & window)
{
	for (auto &i : m_entities)
	{
		i.first->draw(window);
	}
}

bool EntityManager::removeActiveEntity(unsigned int id)
{
	for (auto iter = m_entities.begin(); iter != m_entities.end(); iter++)
	{
		if (iter->first->getID() == id)
		{
			iter = m_entities.erase(iter);
			return true;
		}
	}
	return false;
}

void EntityManager::checkCollisions()
{
	//Dont allow for the same entity to check collision on self
	for (auto iter1 = m_entities.begin(); iter1 != m_entities.end(); iter1++)
	{
		for (auto iter2 = std::next(iter1, 1); iter2 != m_entities.end(); iter2++)
		{
			if (iter1->first->getAABB().intersects(iter2->first->getAABB()))
			{
				//Apply collisions on both entities
				iter1->first->onEntityCollision(iter2->first);
				iter2->first->onEntityCollision(iter1->first);
			}
		}
	}
}

void EntityManager::purgeEntities()
{
	m_entities.clear();
}
