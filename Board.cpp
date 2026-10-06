#include "Board.hpp"

Board::Board(sf::Vector2f position, sf::Vector2f size)
: m_rectangle(size)
{
	m_rectangle.setPosition(position);
	m_rectangle.setFillColor(sf::Color::Black);
}

void Board::DrawBoard(sf::RenderWindow& window) const
{
	window.draw(m_rectangle);
}

sf::FloatRect Board::GetBounds() const
{
	return m_rectangle.getGlobalBounds();
}