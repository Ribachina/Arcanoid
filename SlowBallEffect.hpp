#pragma once
#include "BonusEffect.hpp"
#include "Ball.hpp"

// ”меньшает скорость м€ча
class SlowBallEffect : public BonusEffect
{
public:
	SlowBallEffect(Ball& ball);

	void Apply() override;
	void Remove() override;

private:
	Ball& m_ball;

	static constexpr float SPEED_FACTOR = 0.7f;
};