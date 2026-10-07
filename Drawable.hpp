#pragma once

#include <SFML/Graphics.hpp>

// Интерфейс для отрисовки
class Drawable
{
public:
	virtual ~Drawable() = default;
	
	virtual void Draw(sf::RenderWindow& window) const = 0;
};