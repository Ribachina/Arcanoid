#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateData.hpp"
#include "GameConfig.hpp"
#include <vector>

// Состояние победы, показывает сообщение о победе и предлагает начать игру заново или вернуться в меню
class VictoryStateData : public GameStateData
{
public:
	VictoryStateData(const sf::Font& font, int score, const std::vector<int>& scores); // Конструктор текста и очков
	
	void Init() override;
	void HandleWindowEvent(const sf::Event& event) override; // запрос: Y - NewGame, N - MainMenu
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window) override;

private:
	sf::Text m_title;
	sf::Text m_question;
	sf::Text m_scoreTitle;
	sf::Text m_leaderboardText;
	
	int m_score; // Результат текущей игры
	std::vector<int>m_scores; // Результат рекордов
};