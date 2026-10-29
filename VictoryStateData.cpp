#include "VictoryStateData.hpp"

VictoryStateData::VictoryStateData(const sf::Font& font, int score, const std::vector<int>& scores)
	:m_title(font, "YOU WIN", 80),
	m_question(font, "Restart?\nPress Y/N", 40),
	m_scoreTitle(font, "Score: 0", 30),
	m_leaderboardText(font, "", 30),
	m_score(score),
	m_scores(scores)
{
}

void VictoryStateData::Init()
{
	m_title.setFillColor(sf::Color::Green);
	m_title.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_title), 100.f});
	
	m_question.setFillColor(sf::Color::White);
	m_question.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_question), 200.f });

	m_scoreTitle.setString("Score: " + std::to_string(m_score));
	m_scoreTitle.setFillColor(sf::Color::White);
	m_scoreTitle.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_scoreTitle), 300.f });

	std::string leaderboardString = "TOP 5\n";
	for (std::size_t i = 0; i < m_scores.size() && i < 5; ++i)
	{
		leaderboardString += std::to_string(i + 1) + ". " + std::to_string(m_scores[i]) + '\n';
	}

	m_leaderboardText.setString(leaderboardString);
	m_leaderboardText.setFillColor(sf::Color::White);
	m_leaderboardText.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_leaderboardText), 380.f });
}

void VictoryStateData::HandleWindowEvent(const sf::Event& event)
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

void VictoryStateData::Update(float deltaTime)
{
}

void VictoryStateData::Draw(sf::RenderWindow& window)
{
	window.draw(m_title);
	window.draw(m_question);
	window.draw(m_scoreTitle);
	window.draw(m_leaderboardText);
}
