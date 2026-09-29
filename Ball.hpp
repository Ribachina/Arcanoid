#pragma once
#include <SFML/Graphics.hpp>
#include "Board.hpp"

class Ball
{
public:
	// Создаём шар с заданной позицей, скоростью и радиусом
	Ball(sf::Vector2f position, sf::Vector2f initialVelocity, float radius);

	void Update(const Board& board, float deltaTime); // Обновляем состояние шара
	void DrawBall(sf::RenderWindow& window) const; // Рисуем шар
	void Launch(); // Запускаем шар с платформы
	void AttachTo(const sf::FloatRect& platformBounds); // Пока шар не запущен, держим его по центру платформы
	void BounceFromPlatform(); // Отражает шар после столкновения с платформой
	void BounceFromBlock();
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
