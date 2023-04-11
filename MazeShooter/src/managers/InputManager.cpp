#include "../../include/managers/InputManager.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/utils/Vector2.h"
#include "../../include/models/Player.h"
#include "../../include/managers/LevelManager.h"
#include "../../include/managers/WindowManager.h"

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

InputManager::InputManager() {

}

void InputManager::update(sf::Keyboard::Key key, float dt) {
	std::cout << dt << std::endl;
		Vec2f acceleration;
		const float dAcc = 5;
		Player* player = LevelManager::GetInstance()->getCurrent()->getPlayer();
		Level* level = LevelManager::GetInstance()->getCurrent();
		auto window = WindowManager::GetInstance()->GetWindow();
		float rotation = 90;
		switch (key)
		{
			case sf::Keyboard::Up:
				acceleration.y -= dAcc;
				rotation = 270;
				break;
			case sf::Keyboard::Down:
				acceleration.y += dAcc;
				rotation = 90;
				break;
			case sf::Keyboard::Right:
				acceleration.x += dAcc;
				rotation = 0;
				break;
			case sf::Keyboard::Left:
				acceleration.x -= dAcc;
				rotation = 180;
				break;
			case sf::Keyboard::Space:
				level->addBullet();
				break;
			case sf::Keyboard::Escape:
				window->close();
				break;
		}
		acceleration.x += acceleration.x * dt;
		acceleration.y += acceleration.y * dt;
		level->update(acceleration, rotation);
}


