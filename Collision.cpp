#include "Collision.hpp"

bool IsCollision(const sf::FloatRect& first, const sf::FloatRect& second)
{
	const float firstLeft = first.position.x;
	const float firstRight = first.position.x + first.size.x;
	const float firstTop = first.position.y;
	const float firstBottom = first.position.y + first.size.y;

	const float secondLeft = second.position.x;
	const float secondRight = second.position.x + second.size.x;
	const float secondTop = second.position.y;
	const float secondBottom = second.position.y + second.size.y;

	return
		firstRight > secondLeft &&
		firstLeft < secondRight &&
		firstBottom > secondTop &&
		firstTop < secondBottom;
}