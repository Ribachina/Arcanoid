#include "Platform.hpp"

Platform::Platform(sf::Vector2f position, sf::Vector2f size, float speed)
	: m_rectangle(size),
	m_speed(speed)
{
	m_rectangle.setPosition(position);
	m_rectangle.setFillColor(sf::Color::White);
}

void Platform::Update(const Board& board, float deltaTime, MoveDirection direction)
{
	Move(deltaTime, direction);
	CollisionWithWall(board);
}

void Platform::Move(float deltaTime, MoveDirection direction)
{
	const float offset = m_speed * deltaTime;

	switch (direction)
	{
	case MoveDirection::Left:
		m_rectangle.move(sf::Vector2f{ -offset, 0.f });
		break;
	case MoveDirection::Right:
		m_rectangle.move(sf::Vector2f{ offset, 0.f });
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

	const float currentY = m_rectangle.getPosition().y;

	if (platformLeft <= boardLeft)
	{
		m_rectangle.setPosition(sf::Vector2f{ boardLeft, currentY });
	}
	else if (platformRight >= boardRight)
	{
		const float newX = boardRight - platformBounds.size.x;
		m_rectangle.setPosition(sf::Vector2f{ newX, currentY });
	}
}

void Platform::DrawPlatform(sf::RenderWindow& window) const
{
	window.draw(m_rectangle);
}

sf::FloatRect Platform::GetBounds() const
{

	return m_rectangle.getGlobalBounds();
}

