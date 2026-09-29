#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStateData.hpp"
#include "MainMenuStateData.hpp"
#include "PlayingStateData.hpp"
#include "VictoryStateData.hpp"

class Game
{
public:
	Game(); // Создаём окно и начальные объекты

	void Run(); // Главный игровой цикл

private:
	sf::RenderWindow window;
	const sf::Font font;
	std::unique_ptr<GameStateData> currentState;

	

	void Input(); // События окна и команда игрока (запустить шар)
	void Update(float deltaTime); // Обновляем состояние объектов
	void Draw(); // Очищаем и рисуем объекты игры
	void ChangeState(GameStateType type); // Создаёт новое состояние и делает его текущимм
};