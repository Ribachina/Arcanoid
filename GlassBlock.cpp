#include "GlassBlock.hpp"

GlassBlock::GlassBlock(sf::Vector2f position, sf::Vector2f size)
	: Block(position, size)
{
	SetColor(sf::Color::Transparent);
	SetOutline(sf::Color(150, 220, 255), 2.f);
}

bool GlassBlock::OnHit()
{
	Destroy();
	return false;
}




