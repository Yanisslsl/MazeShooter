#pragma once
#include <SFML/Graphics.hpp>
#include "../Events/Event.h"
#include "../../include/core/Eventdispatcher.h"
#include "eventpp/eventdispatcher.h"



class Eventdispatcher
{
public:

	virtual ~Eventdispatcher();
	Eventdispatcher(Eventdispatcher& _other) = delete;
	void operator = (const Eventdispatcher& _other) = delete;
	static Eventdispatcher* GetInstance();
	void InitializeListeners();
	void Dispatch(Event::EventType type, const Event& e);
private:
	Eventdispatcher();
	static Eventdispatcher* m_instance;
	eventpp::EventDispatcher<Event::EventType,void(const Event&)> dispatcher;
};	