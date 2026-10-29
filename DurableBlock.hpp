#pragma once
#include "Block.hpp"
#include "SFML/Graphics.hpp"

// Прочный блок держит 3 удара. Меняет цвет при попадании
class DurableBlock : public Block
{
public:
	DurableBlock(sf::Vector2f position, sf::Vector2f size);
	
	bool OnHit() override;
	int GetScoreValue() const override;

private:
	int m_health = 3;
};