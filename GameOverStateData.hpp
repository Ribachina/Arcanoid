#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateData.hpp"

class GameOverStateData : public GameStateData
{
public:
	GameOverStateData(const sf::Font& font, int score);

	void Init() override;
	void HandleWindowEvent(const sf::Event& event) override;
	void Update(float deltaTime) override;
	void Draw(sf::RenderWindow& window) override;

private:
	sf::Text m_title;
	sf::Text m_scoreText;
	sf::Text m_question;

	int m_score;
};