#include "Block.hpp"

void Block::Draw(sf::RenderWindow& window) const
{
	window.draw(rectangle);
}

sf::FloatRect Block::GetBounds() const
{
	return rectangle.getGlobalBounds();
}


