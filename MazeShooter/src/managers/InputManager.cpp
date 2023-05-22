#include "../../include/managers/InputManager.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/utils/Vector2.h"
#include "../../include/models/Player.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/core/Eventdispatcher.h"
#define ASSETS_PATH "assets/"

InputManager* InputManager::m_instance = nullptr;

InputManager* InputManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new InputManager();
	}

	return m_instance;
}

InputManager::~InputManager()
{
    delete m_instance;
}

InputManager::InputManager() = default;

void InputManager::Update(sf::Keyboard::Key key) {
		const auto dispatcher = Eventdispatcher::GetInstance();
		dispatcher->Dispatch(Event::EventType::INPUT_PLAYER, Event::InputEvent(key));
		if(key == sf::Keyboard::Key::Space)
		{
			dispatcher->Dispatch(Event::EventType::INPUT_BULLET, Event::InputEvent(key));
		}
}


void InputManager::HandleEvent(sf::Event event)
{
	const auto dispatcher = Eventdispatcher::GetInstance();

	switch (event.type)
	{
		case sf::Event::Closed:
			WindowManager::GetInstance()->GetWindow()->close();
			break;
		case sf::Event::KeyPressed:
			Update(event.key.code);
			break;
		case sf::Event::MouseButtonReleased:
			dispatcher->Dispatch(Event::EventType::MOUSE_CLICKED, Event::MouseEvent(Vec2f(event.mouseButton.x, event.mouseButton.y)));
			break;
		default:
			break;
	}
}
