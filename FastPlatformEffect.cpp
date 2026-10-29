#include "FastPlatformEffect.hpp"

FastPlatformEffect::FastPlatformEffect(Platform& platform)
	:m_platform(platform)
{
}

void FastPlatformEffect::Apply()
{
	m_platform.SetSpeed(m_platform.GetSpeed() * SPEED_FACTOR);
}

void FastPlatformEffect::Remove()
{
	m_platform.SetSpeed(m_platform.GetSpeed() / SPEED_FACTOR);
}




