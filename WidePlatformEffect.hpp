#pragma once
#include "BonusEffect.hpp"
#include "Platform.hpp"

// Увеличивает ширину платформы
class WidePlatformEffect : public BonusEffect
{
public:
	WidePlatformEffect(Platform& platform);

	void Apply() override;
	void Remove() override;

private:
	Platform& m_platform;
	sf::Vector2f m_originalSize{};
	static constexpr float WIDTH_FACTOR = 1.5f;
};