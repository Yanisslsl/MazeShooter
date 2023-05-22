#pragma once
#pragma once

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <variant>
#include <unordered_map>
#include "../../include/models/Entity.h"
#include "../../include/models/Player.h"
#include "../../include/models/Bullet.h"
#include "../../include/models/Enemy.h"


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
	Entity* CreateEntity(EntityType type, Vec2f position, float rotation);
	Player* CreatePlayer();
	Bullet* CreateBullet(Vec2f playerPosition, float rotation);
	Enemy* CreateEnemy(Vec2f playerPosition, float rotation);
	Player* GetPlayer();
	void SetCollider(Entity* m_entity, Vec2f _size);
	void DestroyBullet(Entity* entity);
	void DestroyEnemy(Entity* entity);
	void DestroyPlayer();
	std::unordered_map<string, std::variant<std::vector<Entity*>*, Entity*>> getEntities();
private:
	EntityManager();
	static EntityManager* m_instance;
	std::unordered_map<string, std::variant<std::vector<Entity*>*, Entity*>> m_entities;
};
