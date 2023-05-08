#pragma once
#include <SFML/Graphics.hpp>
#include "../Events/Event.h"
#include "../../include/core/EventDispatcher.h"
#include "eventpp/eventdispatcher.h"



class EventDispatcher
{
public:

	virtual ~EventDispatcher();
	EventDispatcher(EventDispatcher& _other) = delete;
	void operator = (const EventDispatcher& _other) = delete;
	static EventDispatcher* GetInstance();
	void initializeListeners();
	void dispatch(Event::EventType type, const Event& e);
private:
	EventDispatcher();
	static EventDispatcher* m_instance;
	eventpp::EventDispatcher<Event::EventType,void(const Event&)> dispatcher;
};	