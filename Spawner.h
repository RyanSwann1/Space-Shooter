#ifndef SPAWNER_H
#define SPAWNER_H

#include "EntityManager.h"
class Spawner
{
public:
	Spawner(EntityManager* entityManager)
		:m_entityManager(entityManager) {}
	
	virtual ~Spawner() {}

	virtual void update(const float timeElasped) {}
	virtual void spawn() {}

protected:
	EntityManager* m_entityManager;
	unsigned int m_minSpawnPos;
	unsigned int m_maxSpawnPos;
	float m_nextSpawnTime;
	float m_timeBetweenSpawn;

};
#endif // !SPAWNER_H