#include "Block.hpp"

void Block::Draw(sf::RenderWindow& window) const
{
	window.draw(m_rectangle);
}

sf::FloatRect Block::GetBounds() const
{
	return m_rectangle.getGlobalBounds();
}


