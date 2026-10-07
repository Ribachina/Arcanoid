#pragma once

#include <SFML/Graphics.hpp>

// Интерфейс для коллизии
class Collidable
{
public:
	virtual ~Collidable() = default;
	
	virtual sf::FloatRect GetBounds() const = 0;
};