#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Board
{
public:
	// Создаём игровое поле с заданной позицией и размером
	Board(sf::Vector2f position, sf::Vector2f size)
		: rectangle(size)
	{
		rectangle.setPosition(position);
		rectangle.setFillColor(sf::Color::Black);
	}

	void DrawBoard(sf::RenderWindow& window) const; // Рисуем игровое поле

	sf::FloatRect GetBounds() const; // Вовращаем глобальные границы игрового поля

private:
	sf::RectangleShape rectangle;
};

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
	Platform(sf::Vector2f position, sf::Vector2f size, float speed)
		: rectangle(size),
		speed(speed)
	{
		rectangle.setPosition(position);
		rectangle.setFillColor(sf::Color::White);
	}
		 
	
	void Update(const Board& board, float deltaTime, MoveDirection direction); // Обновляем состояние платформы: перемещаем и проверяем столкновение с границами Board
	void DrawPlatform(sf::RenderWindow& window) const; // Рисуем платформу
	
	sf::FloatRect GetBounds() const; // Вовращаем глобальные границы платформы

private:
	sf::RectangleShape rectangle;
	float speed;

	void Move(float deltaTime, MoveDirection direction); // Перемещаем платформу в выбранном направлении
	void CollisionWithWall(const Board& board); // Не позволяем платформе выйти за границы поля
};

class Ball
{
public:
	// Создаём шар с заданной позицей, скоростью и радиусом
	Ball(sf::Vector2f position, sf::Vector2f initialVelocity, float radius)
		: initialVelocity(initialVelocity),
		velocity(initialVelocity)
	{
		circle.setPosition(position);
		circle.setRadius(radius);
		circle.setFillColor(sf::Color::White);
	}
	
	void Update(const Board& board, float deltaTime); // Обновляем состояние шара
	void DrawBall(sf::RenderWindow& window) const; // Рисуем шар
	void Launch(); // Запускаем шар с платформы
	void AttachTo(const sf::FloatRect& platformBounds); // Пока шар не запущен, держим его по центру платформы
	void BounceFromPlatform(); // Отражает шар после столкновения с платформой
	void Reset(); // Возвращаем шар в состояние "до запуска" и сбрасываем скорость

	sf::FloatRect GetBounds() const; // Вовращаем глобальные границы шара

private:
	sf::CircleShape circle;
	sf::Vector2f initialVelocity;
	sf::Vector2f velocity;

	bool launched = false;
	

	void Move(float deltaTime); // Перемещаем шар
	void CollisionWithWall(const Board& board); // Проверяем столкновения шара со стенами поля и меняем направление
};

bool IsCollision(const sf::FloatRect& first, const sf::FloatRect& second); // Проверка коллизий (любых прямоугольников)

