#include "../../include/managers/UIManager.h"
#include "../../include/managers/EntityManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/managers/GameManager.h"


UIManager* UIManager::m_instance = nullptr;

UIManager* UIManager::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new UIManager();
	}

	return m_instance;
}

UIManager::~UIManager()
{
	delete m_instance;
}

UIManager::UIManager() {
	m_elements = new std::vector<UIElement*>();
}
void UIManager::Render()
{
	const auto window = WindowManager::GetInstance()->GetWindow();
	for(const auto& element: *m_elements)
	{
		if (auto drawable = std::get_if<sf::Drawable*>(&(element->m_shape)))
		{
			window->draw(**drawable);
		}
		else if (auto rectangleShape = std::get_if<sf::RectangleShape*>(&element->m_shape))
		{
			window->draw(**rectangleShape);
		}
	}
}

void UIManager::CreateButton(Vec2f  _size, Vec2f _position, sf::Color _color, std::string _text, int _textSize, UIElementType _buttonType)
{
	auto font = AssetManager::GetInstance()->GetFont("arial");

	const auto rec = new sf::RectangleShape(_size);
	rec->setFillColor(_color);
	rec->setPosition(_position);

	const auto button = new UIElement();
	button->m_buttonType = _buttonType;
	button->m_shape = rec;
	m_elements->push_back(button);
	if(!_text.empty() && _textSize != 0)
	{
		const auto text = new sf::Text();
		text->setString(_text);
		text->setFont(*font);
		text->setFillColor(sf::Color::White);
		text->setCharacterSize(_textSize);

		const auto textBounds = text->getLocalBounds();
		float textX = _position.x + (_size.x - textBounds.width) / 2.f;
		float textY = _position.y;
		text->setPosition(textX, textY);

		const auto textElement = new UIElement();
		textElement->m_buttonType = UIElementType::DEFAULT;
		textElement->m_shape = text;
		m_elements->push_back(textElement);
	}
}


void UIManager::CreateBackGround(std::string _assetId, Vec2f _size)
{
	sf::Texture* texture = AssetManager::GetInstance()->GetTexture(_assetId);

	if (texture != nullptr)
	{
		const auto background = new UIElement();
		const auto rec = new sf::RectangleShape(_size);
		rec->setTexture(texture);
		background->m_shape = rec;
		background->m_buttonType = UIElementType::DEFAULT;
		m_elements->push_back(background);
	}
}


void UIManager::CreateText(std::string _content, Vec2f _position, sf::Color _color, int _size)
{
	auto font = AssetManager::GetInstance()->GetFont("arial");
	auto text = new UIElement();
	const auto txt = new sf::Text();
	txt->setString(_content);
	txt->setFont(*font);
	txt->setFillColor(_color);
	txt->setPosition(_position);
	txt->setCharacterSize(_size);
	text->m_shape = txt;
	text->m_buttonType = UIElementType::DEFAULT;
	m_elements->push_back(text);
}

void UIManager::HandleClick(Event e)
{
	for (const auto& element : *m_elements)
	{
		if(auto rectangleShape = std::get_if<sf::RectangleShape*>(&element->m_shape))
		{
			if((*rectangleShape)->getGlobalBounds().contains(e.position.x, e.position.y) && element->m_buttonType != UIManager::DEFAULT)
			{
				switch (element->m_buttonType)
				{
				case UIElementType::BUTTON_PLAY:
					GameManager::GetInstance()->GetCurrentScene()->SwitchLevel(Level::LevelType::Maze);
					return;
				case UIElementType::BUTTON_MENU:
					GameManager::GetInstance()->GetCurrentScene()->SwitchLevel(Level::LevelType::MainMenu);
					return;
				case UIElementType::BUTTON_EXIT:
					GameManager::GetInstance()->Quit();
					return;
				}
			}
		}
	
	}

	
}
void UIManager::Clear()
{
	m_elements->clear();
}

UIManager::UIElement* UIManager::GetElementByType(UIElementType _type)
{
	for (const auto& element : *m_elements)
	{
		if (element->m_buttonType == _type)
		{
			return element;
		}
	}
}