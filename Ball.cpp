#include "Ball.hpp"

Ball::Ball(sf::Vector2f position, sf::Vector2f initialVelocity, float radius)
	: initialVelocity(initialVelocity),
	velocity(initialVelocity)
{
	circle.setPosition(position);
	circle.setRadius(radius);
	circle.setFillColor(sf::Color::White);
}

void Ball::Update(const Board& board, float deltaTime)
{
	if (launched)
	{
		Move(deltaTime);
		CollisionWithWall(board);
	}
}

void Ball::Move(float deltaTime)
{
	const sf::Vector2f offset = velocity * deltaTime;

	circle.move(offset);
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

void Ball::DrawBall(sf::RenderWindow& window) const
{
	window.draw(circle);
}

void Ball::Launch()
{
	launched = true;
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

void Ball::BounceFromPlatform()
{
	if (velocity.y > 0)
	{
		velocity.y = -velocity.y;
	}
}

void Ball::BounceFromBlock()
{
	velocity.y = -velocity.y;
}

void Ball::Reset()
{
	launched = false;
	velocity = initialVelocity;
}

sf::FloatRect Ball::GetBounds() const
{

	return circle.getGlobalBounds();
}