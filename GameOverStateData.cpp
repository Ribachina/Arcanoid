#include "GameOverStateData.hpp"
#include "GameConfig.hpp"
#include <string>

GameOverStateData::GameOverStateData(const sf::Font& font, int score)
	: m_title(font, "Game Over", 80),
	m_scoreText(font, "Score: 0", 30),
	m_question(font, "Restart?\nPress Y/N", 40),
	m_score(score)
{
}

void GameOverStateData::Init()
{
	m_title.setFillColor(sf::Color::Red);
	m_title.setPosition({ GameConfig::GetCenteredTextX(m_title), 140.f });

	m_scoreText.setString("Score: " + std::to_string(m_score));
	m_scoreText.setFillColor(sf::Color::White);
	m_scoreText.setPosition({ GameConfig::GetCenteredTextX(m_scoreText), 280.f });

	m_question.setFillColor(sf::Color::White);
	m_question.setPosition({ GameConfig::GetCenteredTextX(m_question), 380.f });
}

void GameOverStateData::HandleWindowEvent(const sf::Event& event)
{
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->code == sf::Keyboard::Key::Y)
		{
			RequestState(GameStateType::Playing);
		}
		else if (keyPressed->code == sf::Keyboard::Key::N)
		{
			RequestState(GameStateType::MainMenu);
		}
	}
}

void GameOverStateData::Update(float deltaTime)
{

}

void GameOverStateData::Draw(sf::RenderWindow& window)
{
	window.draw(m_title);
	window.draw(m_scoreText);
	window.draw(m_question);
}
