#include "GameMemento.hpp"

GameMemento::GameMemento(sf::Vector2f ballPosition, sf::Vector2f platformPosition)
	: m_ballPosition(ballPosition),
	m_platformPosition(platformPosition)
{
}

sf::Vector2f GameMemento::GetBallPosition() const
{
	return m_ballPosition;
}

sf::Vector2f GameMemento::GetPlatformPosition() const
{
	return m_platformPosition;
}


