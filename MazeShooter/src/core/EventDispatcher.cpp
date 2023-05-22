#include "../../include/core/Eventdispatcher.h"
#include "../../include/managers/EntityManager.h"
#include "../../include/managers/UIManager.h"
#include <iostream>

Eventdispatcher* Eventdispatcher::m_instance = nullptr;

Eventdispatcher* Eventdispatcher::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Eventdispatcher();
	}

	return m_instance;
}

Eventdispatcher::Eventdispatcher()
{
	InitializeListeners();
}

Eventdispatcher::~Eventdispatcher()
{
	if (m_instance != nullptr)
	{
		delete m_instance;
	}
}

void Eventdispatcher::InitializeListeners()
{
	dispatcher.appendListener(Event::EventType::INPUT_PLAYER, [](const Event& e)
	{
		EntityManager::GetInstance()->GetPlayer()->MovePlayer(Event::EventType::INPUT_PLAYER, e);
	});
	dispatcher.appendListener(Event::EventType::INPUT_BULLET, [](const Event& e)
	{
		EntityManager::GetInstance()->GetPlayer()->ShootBullet();
	});
	dispatcher.appendListener(Event::EventType::ENEMY_COLLISION, [](const Event& e)
	{
		EntityManager::GetInstance()->GetPlayer()->HandleCollision(e.entity);
	});
	dispatcher.appendListener(Event::EventType::MOUSE_CLICKED, [](const Event& e)
	{
		UIManager::GetInstance()->HandleClick(e);
	});
}

void Eventdispatcher::Dispatch(Event::EventType type, const Event& e)
{
	dispatcher.dispatch(type, e);
}