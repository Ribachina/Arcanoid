#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameStateData.hpp"
#include "GameObject.hpp"
#include "Block.hpp"
#include "GameConfig.hpp"
#include "Board.hpp"
#include "Platform.hpp"
#include "Ball.hpp"
#include "Collision.hpp"

// Владеет игровыми объектами и координирует их взаиможействие
class PlayingStateData : public GameStateData
{
public:
	PlayingStateData(); // Конуструктор: поле, платформа и шар

	void Init() override; // Новая игровая сессия удаляем старые блоки, создаём новые
	void HandleWindowEvent(const sf::Event& event) override; // Обработка событий, пробел - заупскает шар
	void Update(float deltaTime) override; // Обновление игры: двигает шар и платформу, проверка коллизии, удаляет блоки, сбрасывает шар на платформу, проверка победы
	void Draw(sf::RenderWindow& window) override;

private:
	Board board;
	Platform platform;
	Ball ball;

	std::vector<std::unique_ptr<GameObject>> blocks;

	MoveDirection GetMoveDirection() const; // Определяем направление движения платформы по состоянию клавиш <-  ->
};