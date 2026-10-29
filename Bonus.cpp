#include "Bonus.hpp"
#include <utility>

Bonus::Bonus(sf::Vector2f position, std::unique_ptr<BonusEffect> effect, float duration, BonusType type)
	: m_rectangle(SIZE),
	m_effect(std::move(effect)),
	m_duration(duration),
	m_type(type)
{
	m_rectangle.setPosition(position);
	switch (m_type)
	{
	case BonusType::WidePlatform: // Широкая платформа - зелёная
		m_rectangle.setFillColor(sf::Color::Green);
		break;

	case BonusType::SlowBall: // Медленный мяч - голубой
		m_rectangle.setFillColor(sf::Color::Cyan);
		break;

	case BonusType::FastPlatform: // Быстрая платформа - жёлтая
		m_rectangle.setFillColor(sf::Color::Yellow);
		break;
	}
}

void Bonus::Draw(sf::RenderWindow& window) const
{
	if (m_state == BonusState::Falling)
	{
		window.draw(m_rectangle);
	}
}

sf::FloatRect Bonus::GetBounds() const
{
	return m_rectangle.getGlobalBounds();
}

bool Bonus::IsFinished() const
{
	return m_state == BonusState::Finished;
}

void Bonus::Activate()
{
	if (m_state != BonusState::Falling)
	{
		return;
	}

	m_effect->Apply();
	m_state = BonusState::Active;
	m_activeTime = 0.f;
}

void Bonus::Miss()
{
	if (m_state == BonusState::Falling)
	{
		m_state = BonusState::Finished;
	}
}

void Bonus::Cancel()
{
	if (m_state == BonusState::Active)
	{
		m_effect->Remove();
	}

	m_state = BonusState::Finished;
}

void Bonus::Update(float deltaTime)
{
	if (m_state == BonusState::Falling)
	{
		m_rectangle.move({ 0.f, FALL_SPEED * deltaTime });
	}
	else if (m_state == BonusState::Active)
	{
		m_activeTime += deltaTime;

		if (m_activeTime >= m_duration)
		{
			m_effect->Remove();
			m_state = BonusState::Finished;
		}
	}
}

BonusType Bonus::GetType() const
{
	return m_type;
}

bool Bonus::IsActive() const
{
	return m_state == BonusState::Active;
}

void Bonus::RefreshDuration()
{
	if (m_state == BonusState::Active)
	{
		m_activeTime = 0.f;
	}
}

void Bonus::Discard()
{
	if (m_state == BonusState::Falling)
	{
		m_state = BonusState::Finished;
	}
}

bool Bonus::IsFalling() const
{
	return m_state == BonusState::Falling;
}