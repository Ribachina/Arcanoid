#include "Ball.hpp"

Ball::Ball(sf::Vector2f position, sf::Vector2f initialVelocity, float radius)
	: m_initialVelocity(initialVelocity),
	m_velocity(initialVelocity)
{
	m_circle.setPosition(position);
	m_circle.setRadius(radius);
	m_circle.setFillColor(sf::Color::White);
}

void Ball::Update(const Board& board, float deltaTime)
{
	if (m_launched)
	{
		Move(deltaTime);
		CollisionWithWall(board);
	}
}

void Ball::Move(float deltaTime)
{
	const sf::Vector2f offset = m_velocity * deltaTime;

	m_circle.move(offset);
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

	const float currentX = m_circle.getPosition().x;
	const float currentY = m_circle.getPosition().y;

	if (ballLeft <= boardLeft)
	{
		m_circle.setPosition(sf::Vector2f{ boardLeft, currentY });
		m_velocity.x = -m_velocity.x;
	}
	else if (ballRight >= boardRight)
	{
		const float newX = boardRight - ballBounds.size.x;
		m_circle.setPosition(sf::Vector2f{ newX, currentY });
		m_velocity.x = -m_velocity.x;
	}
	else if (ballTop <= boardTop)
	{
		m_circle.setPosition(sf::Vector2f{ currentX, boardTop });
		m_velocity.y = -m_velocity.y;
	}
}

void Ball::DrawBall(sf::RenderWindow& window) const
{
	window.draw(m_circle);
}

void Ball::Launch()
{
	m_launched = true;
}

void Ball::AttachTo(const sf::FloatRect& platformBounds)
{
	if (!m_launched)
	{
		const sf::FloatRect ballBounds = GetBounds();

		const float platformLeft = platformBounds.position.x;
		const float platformTop = platformBounds.position.y;
		const float platformWidth = platformBounds.size.x;

		const float ballWidth = ballBounds.size.x;
		const float ballHeight = ballBounds.size.y;

		const float ballX = platformLeft + (platformWidth - ballWidth) / 2;
		const float ballY = platformTop - ballHeight;

		m_circle.setPosition(sf::Vector2f{ ballX, ballY });
	}
}

void Ball::BounceFromPlatform()
{
	if (m_velocity.y > 0)
	{
		m_velocity.y = -m_velocity.y;
	}
}

void Ball::BounceFromBlock()
{
	m_velocity.y = -m_velocity.y;
}

void Ball::Reset()
{
	m_launched = false;
	m_velocity = m_initialVelocity;
}

sf::FloatRect Ball::GetBounds() const
{

	return m_circle.getGlobalBounds();
}