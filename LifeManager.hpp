#pragma once
#include "GameMemento.hpp"
#include <memory>
#include "GameConfig.hpp"

// Опекун в паттерне Memento. Хранит кол-во жизней и снимок
class LifeManager
{
public:
	int GetLives() const;
	void LoseLife();
	void Save(std::unique_ptr<GameMemento> memento);

	const GameMemento* GetLastMemento() const;

private:
	int m_lives = GameConfig::LIVES;
	std::unique_ptr<GameMemento> m_lastMemento;
};