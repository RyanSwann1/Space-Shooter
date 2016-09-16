#ifndef ENEMY_H
#define ENEMY_H


#include "Character.h"
class Enemy :
	public Character
{
public:
	Enemy(EntityManager* entityManager);
	~Enemy();

	void onEntityCollision(Entity* collision) override;
	void update(const float deltaTime) override;
	void reduceLivesAmount(const int i);

private:
	void fireProjectile();
	sf::Vector2f getFirePos() const { return sf::Vector2f(m_position.x, m_position.y - 60); }	
};
#endif // !ENEMY_H
