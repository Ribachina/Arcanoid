#pragma once
#include <SFML/Graphics.hpp>

// Абстрактный интерфейс для игровых объектов
class GameObject
{
public:
	virtual ~GameObject() = default;

	virtual void Draw(sf::RenderWindow& window) const = 0;
	virtual sf::FloatRect GetBounds() const = 0;
};