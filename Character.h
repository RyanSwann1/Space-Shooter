#ifndef CHARACTER_H
#define CHARACTER_H


#include "Entity.h"
class Character :
	public Entity
{
public:
	Character(EntityManager* entityManager);
	virtual ~Character();

	void move(const Direction dir);
	virtual void reduceLivesAmount(const int i) { m_lives -= i; }
	virtual void addLivesAmount(const int i);

	virtual void update(const float deltaTime) {}

protected:
	virtual void onEntityCollision(Entity* collider) = 0;
	int m_lives;
	int m_maxLives; 
	int m_onDestroyPoint;
	float m_timeElasped;
	float m_nextFireTime;
	float m_timeBetweenFire;
};
#endif // !CHARACTER_H
