#include "../../include/models/Entity.h"
#include "../../include/models/Entity.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/models/Level.h"
#include "../../include/managers/LevelManager.h"

Entity::Entity()
{
	m_sprite = nullptr;
	m_spriteSize = { 0.f, 0.f };
	m_position = { 0.f, 0.f };
	m_velocity = { 0.f, 0.f };
}

Entity::~Entity()
{
	if (m_sprite != nullptr)
	{
		delete m_sprite;
	}
}

void Entity::Render(sf::RenderTarget& _target)
{
	if (m_sprite != nullptr)
	{
		Vec2f position = GetPosition();
		Vec2f size = GetSize();
		m_sprite->setPosition(position * size);
		_target.draw(*m_sprite);
	}
}

void Entity::SetSprite(const std::string& _assetId, const float scale, const Vec2f& _position, const Vec2f& _size)
{
	sf::Texture* texture = AssetManager::GetInstance()->GetTexture(_assetId);

	if (texture != nullptr)
	{
		if (m_sprite != nullptr)
		{
			delete m_sprite;
		}

		m_sprite = new sf::Sprite();
		m_sprite->setTexture(*texture);
		m_sprite->setScale(Vec2f(scale, scale));
		sf::Vector2u textureSize = texture->getSize();
		m_sprite->setOrigin(textureSize.x /2 , textureSize.y /2);


		if (_size.x > 0 && _size.y > 0)
		{
			m_sprite->setTextureRect(sf::IntRect(_position.x, _position.y, _size.x, _size.y));
			m_spriteSize = _size;
		}
		else
		{
			m_spriteSize = { (float)texture->getSize().x, (float)texture->getSize().y };
		}
	}
}

void Entity::SetPosition(const Vec2f& _position)
{
	m_position = _position;
}

Vec2f Entity::GetPosition()
{
	return m_position;
}

void Entity::SetSize(const Vec2f& _size)
{
	m_size = _size;
}

Vec2f Entity::GetSize()
{
	return m_size;
}

void Entity::SetType(Entity::EntityType type)
{
	m_type = type;
}

Entity::EntityType Entity::GetType()
{
	return m_type;
}

Vec2f Entity::GetDirection() const
{
	return m_direction;
}

void Entity::SetDirection(Vec2f direction)
{
	m_direction = direction;
}

void Entity::SetRotation(float angle) {
	m_rotation = angle;
	m_sprite->setRotation(angle);
}

void Entity::updateMovement(const Vec2f& acceleration, float rotation)
{
	auto position = GetPosition();
	float pX = position.x + acceleration.x;
	float pY = position.y + acceleration.y;

	if (isInSameCell(Vec2f(pX, pY))) {
		move(Vec2f(pX, pY), rotation);
	}
	else if (checkCollision(Vec2f(pX, pY), rotation)) {
		move(Vec2f(pX, pY), rotation);
	}
}

bool Entity::isInSameCell(const Vec2f& position)
{
	Level* level = LevelManager::GetInstance()->getCurrent();
	auto currentCellPosition = level->getRelativePositionInLevel(this)->currentLocation;
	if (position.x > currentCellPosition.x + 30) {
		return false;
	}
	else if (position.x < currentCellPosition.x) {
		return false;
	}
	else if (position.y > currentCellPosition.y + 30) {
		return false;
	}
	else if (position.y < currentCellPosition.y) {
		return false;
	}
	return true;
}


bool Entity::checkCollision(const Vec2f& position, float rotation) {
	Level* level = LevelManager::GetInstance()->getCurrent();
	auto currentCell = level->getRelativePositionInLevel(this);
	auto currentLocation = currentCell->currentLocation;

	if (currentCell->avaiblePaths & Level::CELL_PATH_E && position.x > currentLocation.x + 30) {
		return true;
	}
	else if (currentCell->avaiblePaths & Level::CELL_PATH_W && position.x < currentLocation.x) {
		return true;
	}
	else if (currentCell->avaiblePaths & Level::CELL_PATH_N && position.y < currentLocation.y) {
		return true;
	}
	else if (currentCell->avaiblePaths & Level::CELL_PATH_S && position.y > currentLocation.y + 30) {
		return true;
	}
	return false;
}


void Entity::move(Vec2f position, float rotation) {
	SetRotation(rotation);
	SetPosition(Vec2f(position.x, position.y));
}

float Entity::GetRotation()
{
		return m_rotation;
}

