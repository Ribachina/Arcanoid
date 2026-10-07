#include "PlayingStateData.hpp"

PlayingStateData::PlayingStateData()
	:m_board(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT }),
	m_platform(PLATFORM_POSITION, PLATFORM_SIZE, PLATFROM_SPEED),
	m_ball(BALL_POSTION, BALL_VELOCITY, BALL_RADIUS)
{
}

void PlayingStateData::Init()
{
	m_blocks.clear();
	m_blocks.reserve(BLOCK_COLUMNS * BLOCK_ROWS);
	for (int rows = 0; rows < BLOCK_ROWS; ++rows)
	{
		for (int columns = 0; columns < BLOCK_COLUMNS; ++columns)
		{
			const float x = BLOCK_START_X + columns * BLOCK_STEP_X;
			const float y = BLOCK_START_Y + rows * BLOCK_STEP_Y;

			if ((rows + columns) % 3 == 0)
			{
				m_blocks.push_back(std::make_unique<DurableBlock>(sf::Vector2f{ x, y }, BLOCK_SIZE));
			}
			else if ((rows + columns) % 2 == 0)
			{
				m_blocks.push_back(std::make_unique<GlassBlock>(sf::Vector2f{ x, y }, BLOCK_SIZE));
			}
			else
			{
				m_blocks.push_back(std::make_unique<Block>(sf::Vector2f{ x, y }, BLOCK_SIZE));
			}
		}
	}
}

void PlayingStateData::HandleWindowEvent(const sf::Event& event)
{
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->code == sf::Keyboard::Key::Space)
		{
			m_ball.Launch();
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

	m_platform.Update(m_board, deltaTime, direction);
	m_ball.AttachTo(m_platform.GetBounds());
	m_ball.Update(m_board, deltaTime);
	if (IsCollision(m_platform.GetBounds(), m_ball.GetBounds()))
	{
		m_ball.BounceFromPlatform();
	}

	const sf::FloatRect ballBounds = m_ball.GetBounds();
	const sf::FloatRect boardBounds = m_board.GetBounds();

	const float ballBottom = ballBounds.position.y + ballBounds.size.y;
	const float boardBottom = boardBounds.position.y + boardBounds.size.y;
	if (ballBottom >= boardBottom)
	{
		m_ball.Reset();
		m_ball.AttachTo(m_platform.GetBounds());
	}

	for (auto it = m_blocks.begin(); it != m_blocks.end();)
	{
		if (IsCollision(m_ball.GetBounds(), (*it)->GetBounds()))
		{
			const bool shouldBounce = (*it)->OnHit();

			if (shouldBounce)
			{
				m_ball.BounceFromBlock((*it)->GetBounds());
			}
			
			if ((*it)->IsDestroyed())
			{
				it = m_blocks.erase(it);
			}
			else
			{
				++it;
			}
		}
		else
		{
			++it;
		}
	}

	if (m_blocks.empty())
	{
		RequestState(GameStateType::Victory);
	}
}

void PlayingStateData::Draw(sf::RenderWindow& window)
{
	m_board.DrawBoard(window);
	m_platform.DrawPlatform(window);
	m_ball.DrawBall(window);
	for (const auto& block : m_blocks)
	{
		block->Draw(window);
	}
}

