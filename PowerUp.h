#ifndef POWER_UP_H
#define POWER_UP_H

enum class PowerUpType {Health, Weapon};
#include "Entity.h"
class PowerUp :
	public Entity
{
public:
	PowerUp(EntityManager* entityManager);
	virtual ~PowerUp();

	virtual void onEntityCollision(Entity* collider) = 0;
	virtual void update(const float deltaTime) {}

	void move(const Direction dir);
	static PowerUpType getSubType() { return m_powerUpType; }
protected:
	unsigned int m_powerUpValue;
	static PowerUpType m_powerUpType;
};
#endif // !POWER_UP_H
