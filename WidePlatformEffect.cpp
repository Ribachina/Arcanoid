#include "WidePlatformEffect.hpp"

WidePlatformEffect::WidePlatformEffect(Platform& platform)
	: m_platform(platform)
{
}

void WidePlatformEffect::Apply()
{
	m_originalSize = m_platform.GetSize();

	sf::Vector2f newSize = m_originalSize;
	newSize.x *= WIDTH_FACTOR;
	m_platform.SetSize(newSize);
}

void WidePlatformEffect::Remove()
{
	m_platform.SetSize(m_originalSize);
}
