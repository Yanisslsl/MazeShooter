#pragma once
#include <string>
#include "../utils/Vector2.h"
#include <SFML/Graphics.hpp>


class GameManager
{
public:
	virtual ~GameManager();
	GameManager(const GameManager& _other) = delete;
	void operator=(const GameManager& _other) = delete;
	static GameManager* GetInstance();
	float getDeltaTime();
	bool Run(const std::string& _title, const Vec2i& _size);

private:
	GameManager();
	static GameManager* m_instance;
	bool LoadResources();
	float m_deltaTime;
};
