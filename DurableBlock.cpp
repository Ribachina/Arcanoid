#include "DurableBlock.hpp"

DurableBlock::DurableBlock(sf::Vector2f position, sf::Vector2f size)
	: Block(position, size)
{
	SetColor(sf::Color::Green);
}

bool DurableBlock::OnHit()
{
	--m_health;

	if (m_health == 2)
	{
		SetColor(sf::Color::Yellow);
	}
	if (m_health == 1)
	{
		SetColor(sf::Color::Red);
	}
	if (m_health == 0)
	{
		Destroy();
	}
	return true;
}
