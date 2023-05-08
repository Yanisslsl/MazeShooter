#pragma once
#pragma once

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <variant>
#include <unordered_map>
#include <iostream>
#include <stack>
#include "../../include/models/Entity.h"
#include "../../include/models/Player.h"
#include "../../include/models/Bullet.h"

using namespace std;

class EntityManager
{
public:
	virtual ~EntityManager();
	EntityManager(const EntityManager& _other) = delete;
	void operator=(const EntityManager& _other) = delete;
	static EntityManager* GetInstance();
	enum EntityType
	{
		PLAYER,
		ENEMY,
		BULLET,
	};
	Entity* createEntity(EntityType type, Vec2f position, float rotation);
	Player* createPlayer();
	Bullet* createBullet(Vec2f playerPosition, Vec2f direction, float rotation);
	Player* getPlayer();
	void DestroyBullet(Entity* entity);
	std::unordered_map<string, std::variant<std::vector<Entity*>*, Entity*>> getEntities();
private:
	EntityManager();
	static EntityManager* m_instance;
	std::unordered_map<string, std::variant<std::vector<Entity*>*, Entity*>> m_entities;
};
