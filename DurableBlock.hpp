#pragma once
#include "Block.hpp"
#include "SFML/Graphics.hpp"

class DurableBlock : public Block
{
public:
	DurableBlock(sf::Vector2f position, sf::Vector2f size);
	
	bool OnHit() override;

private:
	int m_health = 3;
};