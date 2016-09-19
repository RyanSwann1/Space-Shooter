#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "SharedContext.h"

#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <list>

class EntityManager
{
public:
	EntityManager(SharedContext* sharedContext);
	~EntityManager();

	void addEntity(const EntityType type);
	void addEntity(const EntityType type, Entity* entity);
	void removeEntity(const unsigned int id);
	void processRemovals();

	void update(const float deltaTime);
	void draw(sf::RenderWindow& window);
	void purgeEntities();
	SharedContext* getSharedContext() { return m_sharedContext; }
	sf::Vector2u gameBoundary() const { return m_gameBoundary; }

	template<class T>
	void registerEntity(const EntityType type)
	{
		m_entityFactory[type] = [this]()->Entity*
		{
			return new T(this);
		};
	}

private:
	
	std::unordered_map<EntityType, std::function<Entity*()>> m_entityFactory;

	std::list<std::pair<Entity*, unsigned int>> m_entities; //Entities with a unique identifier
	std::vector<unsigned int> m_entitiesToRemove;
	unsigned int m_entityCount;
	SharedContext* m_sharedContext;
	sf::Vector2u m_gameBoundary; //Entities must stay inline within this boundary

	bool removeActiveEntity(unsigned int id);
	void checkCollisions();
};
#endif // !ENTITY_MANAGER_H
