#pragma once
#include "BonusEffect.hpp"
#include "Platform.hpp"

// Увеличивает скорость платформы
class FastPlatformEffect : public BonusEffect
{
public:
	FastPlatformEffect(Platform& platform);

	void Apply() override;
	void Remove() override;

private:
	Platform& m_platform;

	static constexpr float SPEED_FACTOR = 1.5f;
};