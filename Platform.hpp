#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

// Команды движения платформы
enum class MoveDirection
{
	Left,
	Right,
	None
};

class Platform
{
public:
	// Создаём платформу с заданной позицей, размером и скоростью движения
	Platform(sf::Vector2f position, sf::Vector2f size, float speed);

	void Update(const Board& board, float deltaTime, MoveDirection direction); // Обновляем состояние платформы: перемещаем и проверяем столкновение с границами Board
	void DrawPlatform(sf::RenderWindow& window) const; // Рисуем платформу

	sf::FloatRect GetBounds() const; // Вовращаем глобальные границы платформы

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f position);

	sf::Vector2f GetSize() const;
	void SetSize(sf::Vector2f size);

	float GetSpeed() const;
	void SetSpeed(float speed);

private:
	sf::RectangleShape m_rectangle;
	float m_speed;

	void Move(float deltaTime, MoveDirection direction); // Перемещаем платформу в выбранном направлении
	void CollisionWithWall(const Board& board); // Не позволяем платформе выйти за границы поля
};