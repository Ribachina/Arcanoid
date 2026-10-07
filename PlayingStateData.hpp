#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameStateData.hpp"
#include "Drawable.hpp"
#include "Collidable.hpp"
#include "Block.hpp"
#include "GameConfig.hpp"
#include "Board.hpp"
#include "Platform.hpp"
#include "Ball.hpp"
#include "Collision.hpp"
#include "DurableBlock.hpp"
#include "GlassBlock.hpp"

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
	static constexpr sf::Vector2f PLATFORM_POSITION{ 375.f, 580.f };
	static constexpr sf::Vector2f PLATFORM_SIZE{ 100.f, 10.f };
	static constexpr float PLATFROM_SPEED = 500.f;

	static constexpr sf::Vector2f BALL_POSTION{ 395.f, 540.f };
	static constexpr sf::Vector2f BALL_VELOCITY{ 500.f, -500.f };
	static constexpr float BALL_RADIUS = 10.f;

	static constexpr int BLOCK_COLUMNS = 10;
	static constexpr int BLOCK_ROWS = 3;
	static constexpr float BLOCK_START_X = 5.f;
	static constexpr float BLOCK_START_Y = 30.f;
	static constexpr float BLOCK_STEP_X = 80.f;
	static constexpr float BLOCK_STEP_Y = 30.f;
	static constexpr sf::Vector2f BLOCK_SIZE{ 70.f, 20.f };
	
	Board m_board;
	Platform m_platform;
	Ball m_ball;

	std::vector<std::unique_ptr<Block>> m_blocks;

	MoveDirection GetMoveDirection() const; // Определяем направление движения платформы по состоянию клавиш <-  ->
};