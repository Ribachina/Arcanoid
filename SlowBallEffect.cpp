#include "SlowBallEffect.hpp"

SlowBallEffect::SlowBallEffect(Ball& ball)
	: m_ball(ball)
{
}

void SlowBallEffect::Apply()
{
	sf::Vector2f velocity = m_ball.GetVelocity();
	velocity *= SPEED_FACTOR;
	m_ball.SetVelocity(velocity);
}

void SlowBallEffect::Remove()
{
	sf::Vector2f velocity = m_ball.GetVelocity();
	velocity /= SPEED_FACTOR;
	m_ball.SetVelocity(velocity);
}


