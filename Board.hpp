#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Board
{
public:
	// Создаём игровое поле с заданной позицией и размером
	Board(sf::Vector2f position, sf::Vector2f size);

	void DrawBoard(sf::RenderWindow& window) const; // Рисуем игровое поле

	sf::FloatRect GetBounds() const; // Вовращаем глобальные границы игрового поля

private:
	sf::RectangleShape m_rectangle;
};