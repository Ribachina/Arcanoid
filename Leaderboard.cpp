#include "Leaderboard.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "GameConfig.hpp"

void Leaderboard::AddScore(int score)
{
	m_scores.push_back(score);

	std::sort(m_scores.begin(), m_scores.end(), std::greater<int>());
}

void Leaderboard::LoadFromFile()
{
	std::ifstream file(GameConfig::LEADERBOARD_FILE);

	if (!file)
	{
		return;
	}

	m_scores.clear();
	int score = 0;

	while (file >> score)
	{
		m_scores.push_back(score);
	}

	std::sort(m_scores.begin(), m_scores.end(), std::greater<int>());
}

void Leaderboard::SaveToFile() const
{
	std::ofstream file(GameConfig::LEADERBOARD_FILE);

	if (!file)
	{
		std::cerr << "Failed to save leaderboard!\n";
		return;
	}

	for (int score : m_scores)
	{
		file << score << '\n';
	}
}

const std::vector<int>& Leaderboard::GetScores() const
{
	return m_scores;
}
