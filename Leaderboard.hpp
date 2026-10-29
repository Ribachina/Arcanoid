#pragma once
#include <vector>

// Хранит таблицу рекордов, сортирует рекорды и загружает/сохраняет их в файл
class Leaderboard
{
public:
	void AddScore(int score);
	void LoadFromFile();
	void SaveToFile() const;

	const std::vector<int>& GetScores() const;

private:
	std::vector<int>m_scores;
};