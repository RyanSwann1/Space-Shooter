#ifndef ENTITY_H
#define ENTITY_H

#include "Direction.h"
#include "AudioPlayer.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>

enum class EntityState { Idle, Move, Attack, Dead };
enum class EntityType { Base, Player, Enemy, Laser, PlayerProjectile, EnemyProjectile, PowerUp, PowerUpHealth, PowerUpProjectile };
//enum class EntityType {Base, Character, Projectie, PowerUp};
//enum class PowerUpType {Health, Weapon};
//enum class CharacterType {Enemy, Player};
//enum class ProjectileType{EnemyProjectile, PlayerProjectile};

struct CollisionElement
{
	CollisionElement(const float area)
		:m_area(area) {}
	float m_area;
};

class EntityManager;
class Entity
{
public:
	Entity(EntityManager* entityManager);
	virtual ~Entity();
	
	void setSize(const sf::Vector2f& size) { m_size = size; updateAABB(); }
	void setVelocity(const sf::Vector2f& velocity) { m_velocity = velocity; updateAABB(); }
	void setTexture(sf::Texture* texture) { m_texture = texture; }
	void setSprite(sf::Texture* texture) { m_sprite.setTexture(*texture); }
	void setID(const unsigned int id) { m_ID = id;  std::cout << m_ID << "\n"; }
	void setName(const std::string& name) { m_name = name; }
	void setStartPos(const sf::Vector2f& startPos) { m_position = startPos; }
	void setDirection(const Direction dir) { m_direction = dir; }
	void setVelocity(const float x, const float y) { m_velocity = sf::Vector2f(x, y); }

	//void set
	int getID() const { return m_ID; }
	EntityType getType() const { return m_entityType; }
	int getDamage() const { return m_onCollisionDamage; }
	sf::Texture* getTexture() { return m_texture; }
	sf::FloatRect getAABB() const { return m_AABB; }

	void draw(sf::RenderWindow& window);
	virtual void update(const float deltaTime);
	void move();

	virtual void onEntityCollision(Entity* collider) = 0;

protected:
	sf::Vector2f m_position;
	sf::Vector2f m_oldPosition;
	sf::Vector2f m_maxVelocity;
	sf::Vector2f m_size;
	sf::Vector2f m_speed;
	sf::Vector2f m_acceleration;
	sf::Vector2f m_velocity;
	sf::Texture* m_texture;
	sf::Sprite m_sprite;

	std::string m_name;
	AudioPlayer m_audioPlayer;
	EntityType m_entityType;
	EntityManager* m_entityManager;
	Direction m_direction;
	sf::FloatRect m_AABB; //Bounding box for the collisions
	int m_ID;
	int m_onCollisionDamage;
	std::vector<CollisionElement> m_collisions;

	inline void updateAABB();
	void applyTexture();
	void drawAABB(sf::RenderWindow& window);
};
#endif // !ENTITY_H