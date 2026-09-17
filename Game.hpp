#pragma once

#include <SFML/Graphics.hpp>
#include "Arcanoid.hpp"

class Game
{
public:
	Game(); // Создаём окно и начальные объекты

	void Run(); // Главный игровой цикл

private:
	sf::RenderWindow window;

	Board board;
	Platform platform;
	Ball ball;

	MoveDirection GetMoveDirection() const; // Определяем направление движения платформы по состоянию клавиш <-  ->

	void Input(); // События окна и команда игрока (запустить шар)
	void Update(float deltaTime); // Обновляем состояние объектов
	void Draw(); // Очищаем и рисуем объекты игры
};