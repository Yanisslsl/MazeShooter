#pragma once
#include <string>
#include "../utils/Vector2.h"
#include <SFML/Graphics.hpp>
#include "../../include/models/Scene.h"


class GameManager
{
public:
	virtual ~GameManager();
	GameManager(const GameManager& _other) = delete;
	void operator=(const GameManager& _other) = delete;
	static GameManager* GetInstance();
	float GetDeltaTime();
	bool Run(const std::string& _title, const Vec2i& _size);
	void AddScene(Scene* _scene);
	Scene* GetCurrentScene();
	void SetCurrentScene(Scene* _scene);
	void Quit();
	void InitializeScenes();
private:
	GameManager();
	static GameManager* m_instance;
	bool LoadResources();
	float m_deltaTime;
	std::vector<Scene*> m_scenes;
	Scene* m_currentScene;
};
