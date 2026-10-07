#include "Block.hpp"


	Block::Block(sf::Vector2f position, sf::Vector2f size)
		: m_rectangle(size)
{
		m_rectangle.setPosition(position);
		m_rectangle.setFillColor(sf::Color::White);
}

void Block::Draw(sf::RenderWindow& window) const
{
	window.draw(m_rectangle);
}

sf::FloatRect Block::GetBounds() const
{
	return m_rectangle.getGlobalBounds();
}

bool Block::OnHit()
{
	Destroy();
	return true;
}

bool Block::IsDestroyed() const
{
	return m_destroyed;
}

void Block::SetColor(sf::Color color)
{
	m_rectangle.setFillColor(color);
}

void Block::SetOutline(sf::Color color, float thickness)
{
	m_rectangle.setOutlineColor(color);
	m_rectangle.setOutlineThickness(thickness);
}

void Block::Destroy()
{
	m_destroyed = true;
}


