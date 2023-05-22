#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "../utils/Vector2.h"
#include "../../include/Events/Event.h"
#include <variant>


class UIManager
{
public:
	enum UIElementType
	{
		BUTTON_PLAY,
		BUTTON_EXIT,
		BUTTON_MENU,
		HEALTH_BAR,
		DEFAULT
	};
	struct UIElement
	{
		std::variant<sf::Drawable*, sf::RectangleShape*> m_shape;
		Vec2f m_position;
		Vec2f m_size;
		UIElementType m_buttonType;
	};
	virtual ~UIManager();
	UIManager(const UIManager& _other) = delete;
	void operator=(const UIManager& _other) = delete;
	static UIManager* GetInstance();
	void Render();
	void CreateButton(Vec2f _size, Vec2f _position, sf::Color _color, std::string _text = "", int _textSize = 0, UIElementType _buttonType = UIElementType::DEFAULT);
	void CreateBackGround(std::string _assetId, Vec2f _size);
	void CreateText(std::string _content, Vec2f _position, sf::Color _color, int _size);
	void HandleClick(Event e);
	void Clear();
	UIElement* GetElementByType(UIElementType _type);
private:
	UIManager();
	static UIManager* m_instance;
	UIElement* m_healthBar;
	std::vector<UIElement*>* m_elements;
};
#pragma once
