#pragma once
#include "Block.hpp"
#include "SFML/Graphics.hpp"

class GlassBlock : public Block
{
public:
	GlassBlock(sf::Vector2f position, sf::Vector2f size);

	bool OnHit() override;
};