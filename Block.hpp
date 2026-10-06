#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "GameObject.hpp"

// Разрушаемый блок игры, который реализует интрефейс GameObject
class Block : public GameObject
{
public:
	// Создаём блок с позицей и размером
	Block(sf::Vector2f position, sf::Vector2f size)
		: m_rectangle(size)
	{
		m_rectangle.setPosition(position);
		m_rectangle.setFillColor(sf::Color::White);
	}

	void Draw(sf::RenderWindow& window) const override;
	sf::FloatRect GetBounds() const override;

private:
	sf::RectangleShape m_rectangle;
};