#ifndef POWER_UP_HEALTH
#define POWER_UP_HEALTH


#include "PowerUp.h"
class PowerUpHealth :
	public PowerUp
{
public:
	PowerUpHealth(EntityManager* entityManager);
	~PowerUpHealth();

	void onEntityCollision(Entity* collider);
	void update(const float deltaTime) override;
private:

};
#endif // !POWER_UP_HEALTH
