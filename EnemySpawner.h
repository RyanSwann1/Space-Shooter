#ifndef ENEMY_SPAWNER_H
#define ENEMY_SPAWNER_H


#include "Spawner.h"
class EnemySpawner :
	public Spawner
{
public:
	EnemySpawner(EntityManager* entityManager);
	~EnemySpawner();

	void update(const float timeElasped) override;
	void spawn() override;
};
#endif // !ENEMY_SPAWNER_H
