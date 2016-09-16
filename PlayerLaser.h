#ifndef PLAYER_LASER_H
#define PLAYER_LASER_H


#include "Projectile.h"
class PlayerLaser :
	public Projectile
{
public:
	PlayerLaser(EntityManager* entityManager);
	~PlayerLaser();

	void update(const float deltaTime) override;
	void onEntityCollision(Entity* collider) override;
private:

};
#endif // !PLAYER_LASER_H
