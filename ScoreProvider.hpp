#pragma once

// Интерфейс для чтения текущего количества очков
class ScoreProvider
{
public:
	virtual ~ScoreProvider() = default;

	virtual int GetScore() const = 0;
};