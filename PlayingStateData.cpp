#include "PlayingStateData.hpp"

PlayingStateData::PlayingStateData()
	:board(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT }),
	platform(sf::Vector2f{ 375.f, 580.f }, sf::Vector2f{ 100.f, 10.f }, 500.f),
	ball(sf::Vector2f{ 395.f, 540.f }, sf::Vector2f{ 500.f, -500.f }, 10.f)
{
}

void PlayingStateData::Init()
{
	blocks.clear();
	blocks.reserve(10);
	for (int i = 0; i < 10; ++i)
	{
		const float x = 50.f + i * 70.f;
		const float y = 50.f;

		blocks.push_back(std::make_unique<Block>(sf::Vector2f{ x, y }, sf::Vector2f{ 60.f, 20.f }));
	}
}

void PlayingStateData::HandleWindowEvent(const sf::Event& event)
{
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->code == sf::Keyboard::Key::Space)
		{
			ball.Launch();
		}
	}
}

MoveDirection PlayingStateData::GetMoveDirection() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		return MoveDirection::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		return MoveDirection::Right;
	}

	return MoveDirection::None;
}

void PlayingStateData::Update(float deltaTime)
{
	const MoveDirection direction = GetMoveDirection();

	platform.Update(board, deltaTime, direction);
	ball.AttachTo(platform.GetBounds());
	ball.Update(board, deltaTime);
	if (IsCollision(platform.GetBounds(), ball.GetBounds()))
	{
		ball.BounceFromPlatform();
	}

	const sf::FloatRect ballBounds = ball.GetBounds();
	const sf::FloatRect boardBounds = board.GetBounds();

	const float ballBottom = ballBounds.position.y + ballBounds.size.y;
	const float boardBottom = boardBounds.position.y + boardBounds.size.y;
	if (ballBottom >= boardBottom)
	{
		ball.Reset();
		ball.AttachTo(platform.GetBounds());
	}

	for (auto it = blocks.begin(); it != blocks.end();)
	{
		if (IsCollision(ball.GetBounds(), (*it)->GetBounds()))
		{
			ball.BounceFromBlock();
			it = blocks.erase(it);
		}
		else
		{
			++it;
		}
	}

	if (blocks.empty())
	{
		RequestState(GameStateType::Victory);
	}
}

void PlayingStateData::Draw(sf::RenderWindow& window)
{
	board.DrawBoard(window);
	platform.DrawPlatform(window);
	ball.DrawBall(window);
	for (const auto& block : blocks)
	{
		block->Draw(window);
	}
}

