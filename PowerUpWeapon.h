#pragma once
#include "PowerUp.h"
class PowerUpWeapon :
	public PowerUp
{
public:
	PowerUpWeapon(EntityManager* entityManager);
	~PowerUpWeapon();


	void onEntityCollision(Entity* collider) override;
	void update(const float deltaTime) override;
private:

};

