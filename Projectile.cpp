#include "Projectile.h"



Projectile::Projectile(EntityManager* entityManager)
	: Entity(entityManager)
{
	m_name = "Projectile";
	m_name = "Player_Laser";
	Entity::applyTexture();
}


Projectile::~Projectile()
{
}

void Projectile::move(const Direction dir)
{
	switch (dir)
	{
	case (Direction::Up) :
	{
		setVelocity(0, -m_speed.y);
		break;
	}
	case (Direction::Down) :
	{
		setVelocity(0, m_speed.y);
		break;
	}
	}
}
