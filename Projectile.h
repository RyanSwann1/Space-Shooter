#ifndef PROJECTILE_H
#define PROJECTILE_H

enum class ProjectileType { PlayerProjectile, EnemyProjectile };

#include "Entity.h"
class Projectile :
	public Entity
{
public:
	Projectile(EntityManager* entityManager);
	virtual ~Projectile();

	void move(const Direction dir);
	virtual void update(const float deltaTime) {}
	virtual void onEntityCollision(Entity* collider) {}

protected:
	

};
#endif // !PROJECTILE_H
