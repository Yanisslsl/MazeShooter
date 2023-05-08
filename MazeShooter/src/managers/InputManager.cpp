#include "../../include/managers/InputManager.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/utils/Vector2.h"
#include "../../include/models/Player.h"
#include "../../include/managers/LevelManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/core/EventDispatcher.h"
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

void InputManager::update(sf::Keyboard::Key key) {
		Vec2f acceleration;
		const auto dispatcher = EventDispatcher::GetInstance();
		Player* player = LevelManager::GetInstance()->getCurrent()->getPlayer();
		Level* level = LevelManager::GetInstance()->getCurrent();
		auto window = WindowManager::GetInstance()->GetWindow();
		float rotation = 90;
		dispatcher->dispatch(Event::EventType::INPUT_PLAYER, { key });
		if(key == sf::Keyboard::Key::Space)
		{
			dispatcher->dispatch(Event::EventType::INPUT_BULLET, { key });
		}
}

