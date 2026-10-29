#pragma once
#include "ScoreObserver.hpp"
#include "ScoreProvider.hpp"

// Хранит счёт. Получает события от Observer и даёт значение очков для Provider
class ScoreManager : public ScoreObserver, public ScoreProvider
{
public:
	void OnBlockDestroyed(int scoreValue) override;
	int GetScore() const override;
	void Reset();

private:
	int m_score = 0;
};