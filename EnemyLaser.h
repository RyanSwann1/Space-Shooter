#ifndef ENEMY_LASER_H
#define ENEMY_LASER_H


#include "Projectile.h"
class EnemyLaser :
	public Projectile
{
public:
	EnemyLaser(EntityManager* entityManager);
	~EnemyLaser();

	void onEntityCollision(Entity* collider) override;
	void update(const float deltaTime) override;

private:

}; 
#endif // !ENEMY_LASER_H

