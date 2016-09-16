#include "PowerUpSpawner.h"
#include "PowerUpHealth.h"
#include "PowerUpWeapon.h"
#include "Utilities.h"


PowerUpSpawner::PowerUpSpawner(EntityManager* entityManager)
	:Spawner(entityManager)
{
	m_timeBetweenSpawn = 6;
	m_nextSpawnTime = 4;
	m_minSpawnPos = 25;
	m_maxSpawnPos = 650;
}

PowerUpSpawner::~PowerUpSpawner()
{
}

void PowerUpSpawner::update(const float timeElasped)
{
	if (timeElasped >= m_nextSpawnTime)
	{
		spawn();
		m_nextSpawnTime += m_timeBetweenSpawn;
	}
}

void PowerUpSpawner::spawn()
{
	//Entity* powerup = m_powerUps[0];

	//Select two possible power ups to spawn in game
	auto randNumb = Utilities::getRandomNumber(0, 1);
	if (randNumb == 0) 
	{
		m_entityManager->addEntity(EntityType::PowerUpHealth);
	}
	else 
	{
		m_entityManager->addEntity(EntityType::PowerUpProjectile);
	}
}

