#ifndef POWER_UP_SPAWNER_H
#define POWER_UP_SPAWNER_H

#include "Spawner.h"
#include "PowerUp.h"
#include <vector>
#include <functional>
#include <unordered_map>
class PowerUpSpawner :
	public Spawner
{
public:
	PowerUpSpawner(EntityManager* entityManager);
	~PowerUpSpawner();

	void update(const float timeElasped) override;
	void spawn() override;
};
#endif // !POWER_UP_SPAWNER_H
