#include "PlayingStateData.hpp"
#include <cstdlib>

PlayingStateData::PlayingStateData(ScoreObserver& scoreObserver, const ScoreProvider& scoreProvider, const sf::Font& font)
	:m_board(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT }),
	m_platform(PLATFORM_POSITION, PLATFORM_SIZE, PLATFROM_SPEED),
	m_ball(BALL_POSTION, BALL_VELOCITY, BALL_RADIUS),
	m_scoreObserver(scoreObserver),
	m_bonusFactory(m_platform, m_ball),
	m_scoreProvider(scoreProvider),
	m_livesText(font, " ", 24),
	m_scoreText(font, " ", 24)
{
}

void PlayingStateData::Init()
{
	m_blocks.clear();
	
	for (auto& bonus : m_bonuses)
	{
		bonus->Cancel();
	}
	m_bonuses.clear();

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

	m_lifeManager.Save(CreateMemento());
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
		m_lifeManager.LoseLife();

		for (auto& bonus : m_bonuses)
		{
			bonus->Cancel();
		}
		
		m_bonuses.clear();
		const GameMemento* memento = m_lifeManager.GetLastMemento();

		if (m_lifeManager.GetLives() > 0 && memento)
		{
			RestoreMemento(*memento);
			
			m_ball.Reset();
			m_ball.AttachTo(m_platform.GetBounds());
			return;
		}

		RequestState(GameStateType::GameOver);
		return;
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
				m_scoreObserver.OnBlockDestroyed((*it)->GetScoreValue());

				const sf::Vector2f bonusPosition = (*it)->GetBounds().position;
				if (std::rand() % 10 == 0)
				{
					m_bonuses.push_back(m_bonusFactory.CreateRandomBonus(bonusPosition));
				}
				
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

	for (auto it = m_bonuses.begin(); it != m_bonuses.end();) // Ёффекты одного типа бонуса не складываютс€, только обновл€етс€ таймер эффекта
	{
		(*it)->Update(deltaTime);

		if ((*it)->IsFalling() && IsCollision((*it)->GetBounds(), m_platform.GetBounds()))
		{
			Bonus* currentBonus = it->get();
			Bonus* activeBonus = nullptr;

			for (const auto& bonus : m_bonuses)
			{
				if (bonus.get() != currentBonus && bonus->IsActive() && bonus->GetType() == currentBonus->GetType())
				{
					activeBonus = bonus.get();
					break;
				}
			}

			if (activeBonus)
			{
				activeBonus->RefreshDuration();
				currentBonus->Discard();
			}
			else
			{
				currentBonus->Activate();
			}
		}

		const sf::FloatRect bonusBounds = (*it)->GetBounds();
		const float bonusBottom = bonusBounds.position.y + bonusBounds.size.y;

		if (bonusBottom >= boardBottom)
		{
			(*it)->Miss();
		}

		if ((*it)->IsFinished())
		{
			it = m_bonuses.erase(it);
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

	m_scoreText.setString("Score: " + std::to_string(m_scoreProvider.GetScore()));
	const sf::FloatRect scoreBounds = m_scoreText.getLocalBounds();
	m_scoreText.setPosition({ GameConfig::WINDOW_WIDTH - scoreBounds.size.x - scoreBounds.position.x - 10.f, 0.f });

	m_livesText.setString("Lives: " + std::to_string(m_lifeManager.GetLives()));
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

	for (const auto& bonus : m_bonuses)
	{
		bonus->Draw(window);
	}

	window.draw(m_livesText);
	window.draw(m_scoreText);
}

std::unique_ptr<GameMemento> PlayingStateData::CreateMemento() const
{
	return std::make_unique<GameMemento>(m_ball.GetPosition(), m_platform.GetPosition());
}

void PlayingStateData::RestoreMemento(const GameMemento& memento)
{
	m_ball.SetPosition(memento.GetBallPosition());
	m_platform.SetPosition(memento.GetPlatformPosition());
}
