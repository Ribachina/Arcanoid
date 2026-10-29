#pragma once
#include "Block.hpp"
#include "SFML/Graphics.hpp"

// Стеклянный блок. Ball не отражается
class GlassBlock : public Block
{
public:
	GlassBlock(sf::Vector2f position, sf::Vector2f size);

	bool OnHit() override;
	int GetScoreValue() const override;
};