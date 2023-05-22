#include "../../include/models/Entity.h"
#include "../../include/models/Entity.h"
#include "../../include/managers/AssetManager.h"
#include "../../include/managers/WindowManager.h"
#include "../../include/managers/EntityManager.h"
#include "../../include/models/Level.h"
#include "../../include/models/MazeLevel.h"
#include "../../include/managers/GameManager.h"


Entity::Entity()
{
	m_sprite = nullptr;
	m_spriteSize = { 0.f, 0.f };
	m_position = { 0.f, 0.f };
	m_velocity = { 0.f, 0.f };
	m_collider = nullptr;
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
		const auto position = GetPosition();
		const auto size = GetSize();
		m_sprite->setPosition(position * size);
		const auto collider = GetCollider();
		collider->GetCollider()->setPosition(GetCollider()->GetPosition());

		_target.draw(*collider->GetCollider());
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

Entity::Direction Entity::GetDirection() 
{
	return m_direction;
}

void Entity::SetDirection(Entity::Direction direction)
{
	m_direction = direction;
}

void Entity::SetRotation(float angle) {
	m_rotation = angle;
	m_sprite->setRotation(angle);
}

void Entity::UpdateMovement(const Vec2f& acceleration, float rotation)
{
	const auto position = GetPosition();
	const float pX = position.x + acceleration.x;
	const float pY = position.y + acceleration.y;

	if (IsInSameCell(Vec2f(pX, pY), 10)) {
		Move(Vec2f(pX, pY), rotation);
	}
	else if (CheckCollision(Vec2f(pX, pY), rotation, 10)) {
		Move(Vec2f(pX, pY), rotation);
	}
}

bool Entity::IsInSameCell(const Vec2f& position, int padding)
{
	const auto currentLevel = GameManager::GetInstance()->GetCurrentScene()->GetCurrentLevel();
	const auto currentCellPosition = dynamic_cast<MazeLevel*>(currentLevel)->GetRelativePositionInLevel(this)->currentLocation;

	if (position.x + padding > currentCellPosition.x + 30) {
		return false;
	}
	else if (position.x - padding < currentCellPosition.x) {
		return false;
	}
	else if (position.y + padding > currentCellPosition.y + 30) {
		return false;
	}
	else if (position.y - padding < currentCellPosition.y) {
		return false;
	}
	return true;
}


bool Entity::CheckCollision(const Vec2f& position, float rotation, int padding) {
	const auto currentLevel = GameManager::GetInstance()->GetCurrentScene()->GetCurrentLevel();
	const auto currentCellPosition = dynamic_cast<MazeLevel*>(currentLevel)->GetRelativePositionInLevel(this)->currentLocation;
	const auto currentCell = dynamic_cast<MazeLevel*>(currentLevel)->GetRelativePositionInLevel(this);
	const auto currentLocation = currentCell->currentLocation;

	if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_E && position.x + padding > currentLocation.x + 30) {
		return true;
	}
	else if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_W && position.x - padding < currentLocation.x) {
		return true;
	}
	else if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_N && position.y - padding < currentLocation.y) {
		return true;
	}
	else if (currentCell->avaiblePaths & MazeLevel::CELL_PATH_S && position.y + padding > currentLocation.y + 30) {
		return true;
	}
	return false;
}


void Entity::Move(Vec2f position, float rotation) {
	SetRotation(rotation);
	SetPosition(Vec2f(position.x, position.y));
	const auto Position = GetPosition();
	const auto rectangleSize = GetCollider()->GetCollider()->getSize();
	const auto size = GetSize();
	const auto rectPosX = Position.x + size.x / 2.0f - rectangleSize.x / 2.0f;
	const auto rectPosY = Position.y + size.y / 2.0f - rectangleSize.y / 2.0f;
	GetCollider()->SetPosition(Vec2f(rectPosX, rectPosY));
}

float Entity::GetRotation()
{
	return m_rotation;
}

Collider* Entity::GetCollider()
{
	return m_collider;
}


void Entity::SetCollider(Collider* collider)
{
		m_collider = collider;
}

float Entity::GetHealth()
{
	return m_health;
}

void Entity::SetHealth(float health)
{
	m_health = health;
}

void Entity::takeDamage(float damage)
{
	m_health -= damage;
	SetHealth(m_health);

	if (m_health <= 0)
	{
		if(GetType() == EntityType::ENEMY)
		{
			EntityManager::GetInstance()->DestroyEnemy(this);
		} else
		{
			const auto mazeLevel = dynamic_cast<MazeLevel*>(GameManager::GetInstance()->GetCurrentScene()->GetCurrentLevel());
			mazeLevel->GameOver();
		}
	}
}

