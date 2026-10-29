#pragma once
#include <SFML/Graphics.hpp>
#include <string>

// Раньше называли Constant.h Общие параметры игры, которые используются часто и менять их не надо
namespace GameConfig
{
	// ПОСТОЯННЫЕ Размеры окна
	constexpr unsigned WINDOW_WIDTH = 800;
	constexpr unsigned WINDOW_HEIGHT = 600;

	// Сделал ф-ию, чтобы текст распологался по центру (inline определение функции в header)
	inline float GetCenteredTextX(const sf::Text& text)
	{
		const sf::FloatRect bounds = text.getLocalBounds();

		return (WINDOW_WIDTH - bounds.size.x) / 2.f - bounds.position.x;
	}

	const std::string LEADERBOARD_FILE = "leaderboard.txt"; // Файл с рекордами
	const int LIVES = 3;
}