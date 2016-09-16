#include "EnemySpawner.h"
#include "Enemy.h"
#include "Utilities.h"

EnemySpawner::EnemySpawner(EntityManager* entityManager)
	:Spawner(entityManager)
{
	m_minSpawnPos = (0 + 25);
	m_maxSpawnPos = entityManager->getSharedContext()->m_window->getSize().x - 40;
	m_nextSpawnTime = 1;
	m_timeBetweenSpawn = 3;
}


EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update(const float timeElasped)
{
	if (timeElasped >= m_nextSpawnTime)
	{
		std::cout << "Spawn" << "\n";
		m_nextSpawnTime += m_timeBetweenSpawn;
		spawn();
	}
}

void EnemySpawner::spawn()
{
	Entity* enemy = new Enemy(m_entityManager);
	enemy->setStartPos(sf::Vector2f(Utilities::getRandomNumber(m_minSpawnPos, m_maxSpawnPos), 680));
	m_entityManager->addEntity(EntityType::Enemy, enemy);
}
