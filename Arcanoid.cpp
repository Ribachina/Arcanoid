#include "Arcanoid.hpp"


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

void Board::DrawBoard(sf::RenderWindow& window) const
{
	window.draw(rectangle);
}

void Ball::CollisionWithWall(const Board& board)
{
	const sf::FloatRect ballBounds = GetBounds();
	const sf::FloatRect boardBounds = board.GetBounds();

	const float ballLeft = ballBounds.position.x;
	const float ballRight = ballBounds.position.x + ballBounds.size.x;
	const float ballTop = ballBounds.position.y;
	//float ballBottom = ballBounds.position.y + ballBounds.size.y;

	const float boardLeft = boardBounds.position.x;
	const float boardRight = boardBounds.position.x + boardBounds.size.x;
	const float boardTop = boardBounds.position.y;
	//float  boardBottom = boardBounds.position.y + boardBounds.size.y;

	const float currentX = circle.getPosition().x;
	const float currentY = circle.getPosition().y;

	if (ballLeft <= boardLeft)
	{
		circle.setPosition(sf::Vector2f{ boardLeft, currentY });
		velocity.x = -velocity.x;
	}
	else if (ballRight >= boardRight)
	{
		const float newX = boardRight - ballBounds.size.x;
		circle.setPosition(sf::Vector2f{ newX, currentY });
		velocity.x = -velocity.x;
	}
	else if (ballTop <= boardTop)
	{
		circle.setPosition(sf::Vector2f{ currentX, boardTop });
		velocity.y = -velocity.y;
	}
}

void Ball::AttachTo(const sf::FloatRect& platformBounds)
{
	if (!launched)
	{
		const sf::FloatRect ballBounds = GetBounds();

		const float platformLeft = platformBounds.position.x;
		const float platformTop = platformBounds.position.y;
		const float platformWidth = platformBounds.size.x;

		const float ballWidth = ballBounds.size.x;
		const float ballHeight = ballBounds.size.y;

		const float ballX = platformLeft + (platformWidth - ballWidth) / 2;
		const float ballY = platformTop - ballHeight;

		circle.setPosition(sf::Vector2f{ ballX, ballY });
	}
}

void Ball::Update(const Board& board, float deltaTime)
{
	if (launched)
	{
		Move(deltaTime);
		CollisionWithWall(board);
	}
}

void Ball::DrawBall(sf::RenderWindow& window) const
{
	window.draw(circle);
}

void Ball::Launch()
{
	launched = true;
}

void Ball::BounceFromPlatform()
{
	if (velocity.y > 0)
	{
		velocity.y = -velocity.y;
	}
}

void Ball::Reset()
{
	launched = false;
	velocity = initialVelocity;
}

sf::FloatRect Board::GetBounds() const
{
	
	return rectangle.getGlobalBounds();
}

void Ball::Move(float deltaTime)
{
	const sf::Vector2f offset = velocity * deltaTime;

	circle.move(offset);
}

sf::FloatRect Ball::GetBounds() const
{

	return circle.getGlobalBounds();
}




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
