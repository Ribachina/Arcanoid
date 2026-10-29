#include "BonusFactory.hpp"
#include "WidePlatformEffect.hpp"
#include "SlowBallEffect.hpp"
#include "FastPlatformEffect.hpp"
#include <cstdlib>

BonusFactory::BonusFactory(Platform& platform, Ball& ball)
	: m_platform(platform),
	m_ball(ball)
{
}

std::unique_ptr<Bonus> BonusFactory::CreateWidePlatformBonus(sf::Vector2f position)
{
	auto effect = std::make_unique<WidePlatformEffect>(m_platform);
	
	return std::make_unique<Bonus>(position, std::move(effect), BONUS_DURATION, BonusType::WidePlatform);
}

std::unique_ptr<Bonus> BonusFactory::CreateSlowBallBonus(sf::Vector2f position)
{
	auto effect = std::make_unique<SlowBallEffect>(m_ball);
	
	return std::make_unique<Bonus>(position, std::move(effect), BONUS_DURATION, BonusType::SlowBall);
}

std::unique_ptr<Bonus> BonusFactory::CreateFastPlatformBonus(sf::Vector2f position)
{
	auto effect = std::make_unique<FastPlatformEffect>(m_platform);
	
	return std::make_unique<Bonus>(position, std::move(effect), BONUS_DURATION, BonusType::FastPlatform);
}

std::unique_ptr<Bonus> BonusFactory::CreateRandomBonus(sf::Vector2f position)
{
	const int type = std::rand() % 3;

	switch (type)
	{
	case 0:
		return CreateWidePlatformBonus(position);

	case 1:
		return CreateSlowBallBonus(position);

	case 2:
		return CreateFastPlatformBonus(position);
	}

	return nullptr;
}
