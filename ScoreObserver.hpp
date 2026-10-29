#pragma once

// Интерфейс наблюдателя. Узнаёт об уничтожении блока
class ScoreObserver
{
public:
	virtual ~ScoreObserver() = default;

	virtual void OnBlockDestroyed(int scoreValue) = 0;
};