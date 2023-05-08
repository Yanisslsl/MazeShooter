#include "../../include/managers/EntityManager.h"
#include "../../include/models/Player.h"
#include "../../include/models/Entity.h"
#include "../../include/models/Bullet.h"




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
}

Entity* EntityManager::createEntity(EntityManager::EntityType type, Vec2f position = Vec2f(10, 10), float rotation = 90)
{
	Entity* entity = nullptr;
	switch (type)
	{
		case EntityManager::PLAYER:
			{
				auto player = new Player(Vec2f(10, 10));
				player->SetSize(Vec2f(1.0f, 1.0f));
				player->SetType(Entity::EntityType::PLAYER);
				entity = player;
				break;
			}
		case EntityManager::BULLET:
			{
				auto bullet = new Bullet(position);
				bullet->SetSize(Vec2f(1.0f, 1.0f));
				bullet->SetType(Entity::EntityType::BULLET);
				bullet->SetRotation(rotation);
				entity = bullet;
				break;
			}
	}


	return entity;
}

Player* EntityManager::createPlayer()
{
	Entity* player = createEntity(EntityManager::EntityType::PLAYER);
	m_entities["player"] = player;
	return static_cast<Player*>( player);
}

Player* EntityManager::getPlayer()
{
	if (auto pPlayer = std::get_if<Entity*>(&m_entities["player"]))
	{
		return static_cast<Player*>(*pPlayer);
	}
	return nullptr;
}

Bullet* EntityManager::createBullet(Vec2f playerPosition, Vec2f direction, float rotation)
{
	auto bullet = static_cast<Bullet*>(createEntity(EntityManager::EntityType::BULLET, playerPosition, rotation));
	if (auto pVec = std::get_if<std::vector<Entity*>*>(&m_entities["bullets"])) {
		(**pVec).push_back(bullet);
	}
	return static_cast<Bullet*>(bullet);
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
