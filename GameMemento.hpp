#pragma once
#include <SFML/Graphics.hpp>

// —нимок состо€ни€ дл€ восставновлени€ м€ча и платформы после потери жизни
class GameMemento
{
public:
	GameMemento(sf::Vector2f ballPosition, sf::Vector2f platformPosition);

	sf::Vector2f GetBallPosition() const;
	sf::Vector2f GetPlatformPosition() const;

private:
	sf::Vector2f m_ballPosition;
	sf::Vector2f m_platformPosition;
};