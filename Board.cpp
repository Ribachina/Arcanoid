#include "Board.hpp"

Board::Board(sf::Vector2f position, sf::Vector2f size)
: rectangle(size)
{
	rectangle.setPosition(position);
	rectangle.setFillColor(sf::Color::Black);
}

void Board::DrawBoard(sf::RenderWindow& window) const
{
	window.draw(rectangle);
}

sf::FloatRect Board::GetBounds() const
{
	return rectangle.getGlobalBounds();
}