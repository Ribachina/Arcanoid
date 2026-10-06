#include "VictoryStateData.hpp"

VictoryStateData::VictoryStateData(const sf::Font& font)
	:m_title(font, "YOU WIN", 80),
	m_question(font, "Restart?\nPress Y/N", 40)
{
}

void VictoryStateData::Init()
{
	m_title.setFillColor(sf::Color::Green);
	m_title.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_title), 140.f});
	
	m_question.setFillColor(sf::Color::White);
	m_question.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_question), 280.f });
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
}
