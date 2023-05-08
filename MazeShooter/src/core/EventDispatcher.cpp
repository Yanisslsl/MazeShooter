#include "../../include/core/EventDispatcher.h"
#include "../../include/managers/EntityManager.h"
#include <iostream>

EventDispatcher* EventDispatcher::m_instance = nullptr;

EventDispatcher* EventDispatcher::GetInstance()
{
		if (m_instance == nullptr)
		{
					m_instance = new EventDispatcher();
	}

	return m_instance;
}

EventDispatcher::EventDispatcher()
{
	initializeListeners();
}

EventDispatcher::~EventDispatcher()
{
		if (m_instance != nullptr)
		{
					delete m_instance;
		}
}

void EventDispatcher::initializeListeners()
{
	auto player = EntityManager::GetInstance()->getPlayer();
	dispatcher.appendListener(Event::EventType::INPUT_PLAYER, [player](const Event& e)
	{
			player->movePlayer(Event::EventType::INPUT_PLAYER, e);
	});
	dispatcher.appendListener(Event::EventType::INPUT_BULLET, [player](const Event& e)
	{
			player->shootBullet();
	});
}

void EventDispatcher::dispatch(Event::EventType type, const Event& e)
{
		dispatcher.dispatch(type, e);
}