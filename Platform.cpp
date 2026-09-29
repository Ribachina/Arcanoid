#include "Platform.hpp"

Platform::Platform(sf::Vector2f position, sf::Vector2f size, float speed)
	: rectangle(size),
	speed(speed)
{
	rectangle.setPosition(position);
	rectangle.setFillColor(sf::Color::White);
}

void Platform::Update(const Board& board, float deltaTime, MoveDirection direction)
{
	Move(deltaTime, direction);
	CollisionWithWall(board);
}

void Platform::Move(float deltaTime, MoveDirection direction)
{
	const float offset = speed * deltaTime;

	switch (direction)
	{
	case MoveDirection::Left:
		rectangle.move(sf::Vector2f{ -offset, 0.f });
		break;
	case MoveDirection::Right:
		rectangle.move(sf::Vector2f{ offset, 0.f });
		break;
	case MoveDirection::None:
		break;
	}
}

void Platform::CollisionWithWall(const Board& board)
{
	const sf::FloatRect platformBounds = GetBounds();
	const sf::FloatRect boardBounds = board.GetBounds();

	const float platformLeft = platformBounds.position.x;
	const float platformRight = platformBounds.position.x + platformBounds.size.x;

	const float boardLeft = boardBounds.position.x;
	const float boardRight = boardBounds.position.x + boardBounds.size.x;

	const float currentY = rectangle.getPosition().y;

	if (platformLeft <= boardLeft)
	{
		rectangle.setPosition(sf::Vector2f{ boardLeft, currentY });
	}
	else if (platformRight >= boardRight)
	{
		const float newX = boardRight - platformBounds.size.x;
		rectangle.setPosition(sf::Vector2f{ newX, currentY });
	}
}

void Platform::DrawPlatform(sf::RenderWindow& window) const
{
	window.draw(rectangle);
}

sf::FloatRect Platform::GetBounds() const
{

	return rectangle.getGlobalBounds();
}

