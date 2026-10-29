#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Bonus.hpp"
#include "Ball.hpp"
#include "Platform.hpp"

// Фабрика бонусов=)
class BonusFactory
{
public:
	BonusFactory(Platform& platform, Ball& ball);

	std::unique_ptr<Bonus>CreateWidePlatformBonus(sf::Vector2f position);
	std::unique_ptr<Bonus>CreateSlowBallBonus(sf::Vector2f position);
	std::unique_ptr<Bonus>CreateFastPlatformBonus(sf::Vector2f position);

	std::unique_ptr<Bonus>CreateRandomBonus(sf::Vector2f position); // Случайно выбирает один из типов бонусов

private:
	Platform& m_platform;
	Ball& m_ball;

	static constexpr float BONUS_DURATION = 10.f;
};