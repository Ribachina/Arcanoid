#include "ScoreManager.hpp"

void ScoreManager::OnBlockDestroyed(int scoreValue)
{
	m_score += scoreValue;
}

int ScoreManager::GetScore() const
{
	return m_score;
}

void ScoreManager::Reset()
{
	m_score = 0;
}
