#include "../../include/managers/EntityManager.h"
#include "../../include/models/Player.h"
#include "../../include/models/Entity.h"
#include "../../include/models/Bullet.h"
#include "../../include/models/Enemy.h"


EntityManager* EntityManager::m_instance = nullptr;

EntityManager* EntityManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new EntityManager();
	}

	return m_instance;
}

EntityManager::~EntityManager()
{
	delete m_instance;
}

EntityManager::EntityManager() {
	m_entities["bullets"] = new std::vector<Entity*>();
	m_entities["enemies"] = new std::vector<Entity*>();
}

Entity* EntityManager::CreateEntity(EntityManager::EntityType type, Vec2f position = Vec2f(10, 10), float rotation = 90)
{
	Entity* entity = nullptr;
	switch (type)
	{
		case EntityManager::PLAYER:
		{
			const auto player = new Player(Vec2f(1500, 730));
			player->SetSize(Vec2f(1.0f, 1.0f));
			player->SetType(Entity::EntityType::PLAYER);
			SetCollider(player, Vec2f(30, 30));	
			entity = player;
			break;
		}
		case EntityManager::BULLET:
		{
			const auto bullet = new Bullet(position);
			bullet->SetSize(Vec2f(1.0f, 1.0f));
			bullet->SetType(Entity::EntityType::BULLET);
			bullet->SetRotation(rotation);
			SetCollider(bullet, Vec2f(25, 25));
			entity = bullet;
			break;
		}
		case EntityManager::ENEMY:
		{
			const auto enemy = new Enemy(position);
			enemy->SetSize(Vec2f(1.0f, 1.0f));
			enemy->SetType(Entity::EntityType::ENEMY);
			enemy->SetRotation(0);
			SetCollider(enemy, Vec2f(25, 25));
			entity = enemy;
			break;
		}
	}

	return entity;
}

Player* EntityManager::CreatePlayer()
{
	Entity* player = CreateEntity(EntityManager::EntityType::PLAYER);
	m_entities["player"] = player;
	return static_cast<Player*>( player);
}

Player* EntityManager::GetPlayer()
{
	if (auto pPlayer = std::get_if<Entity*>(&m_entities["player"]))
	{
		return static_cast<Player*>(*pPlayer);
	}
	return nullptr;
}

Bullet* EntityManager::CreateBullet(Vec2f playerPosition, float rotation)
{
	const auto bullet = static_cast<Bullet*>(CreateEntity(EntityManager::EntityType::BULLET, playerPosition, rotation));
	if (const auto pVec = std::get_if<std::vector<Entity*>*>(&m_entities["bullets"])) {
		(**pVec).push_back(bullet);
	}
	return bullet;
}

Enemy* EntityManager::CreateEnemy(Vec2f playerPosition, float rotation)
{
	const auto enemy = static_cast<Enemy*>(CreateEntity(EntityManager::EntityType::ENEMY, playerPosition, rotation));
	if (const auto pVec = std::get_if<std::vector<Entity*>*>(&m_entities["enemies"]))
	{
		(**pVec).push_back(enemy);
	}
	return enemy;
}

std::unordered_map<string, std::variant<std::vector<Entity*>*, Entity*>> EntityManager::getEntities()
{
	return m_entities;
}

void EntityManager::DestroyBullet(Entity* entity)
{
	if (auto pVec = std::get_if<std::vector<Entity*>*>(&m_entities["bullets"]))
	{
		auto it = std::find((**pVec).begin(), (**pVec).end(), entity);
		if (it != (**pVec).end())
		{
			(**pVec).erase(it);
		}
	}	
}

void EntityManager::SetCollider(Entity* m_entity, Vec2f _size)
{
	const auto collider = new Collider(m_entity, _size);
	m_entity->SetCollider(collider);
}


void EntityManager::DestroyEnemy(Entity* entity)
{
	if (auto pVec = std::get_if<std::vector<Entity*>*>(&m_entities["enemies"]))
	{
		auto it = std::find((**pVec).begin(), (**pVec).end(), entity);
		if (it != (**pVec).end())
		{
			(**pVec).erase(it);
		}
	}
}

void EntityManager::DestroyPlayer()
{
	if (auto pPlayer = std::get_if<Entity*>(&m_entities["player"]))
	{
		delete *pPlayer;
	}
}
