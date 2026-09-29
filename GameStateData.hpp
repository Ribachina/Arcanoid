#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateType.hpp"

// Абстрактный базовый класс для все состояний
// Определяет общий интерефейс через который работает Game 

class GameStateData
{
public:
	virtual ~GameStateData() = default;

	virtual void Init() = 0;
	virtual void HandleWindowEvent(const sf::Event& event) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(sf::RenderWindow& window) = 0;

	GameStateType GetRequestedState() const
	{
		return requestedState;
	}

protected:
	// Запрашиваем у Game переход в другое состояние
	void RequestState(GameStateType state)
	{
		requestedState = state;
	}

private:
	GameStateType requestedState = GameStateType::None;
};