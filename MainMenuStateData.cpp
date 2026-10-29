#include "MainMenuStateData.hpp"

MainMenuStateData::MainMenuStateData(const sf::Font& font)
	:m_startGameText(font, "Start Game", 40),
	m_hint(font, "Press Enter to start game", 30)
{
}

void MainMenuStateData::Init()
{
	m_startGameText.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_startGameText), 280.f });
	//m_startGameText.setFillColor(sf::Color::White);

	m_hint.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(m_hint), 550.f });
	//m_hint.setFillColor(sf::Color::White);
}

void MainMenuStateData::HandleWindowEvent(const sf::Event& event)
{
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
	{
		if (keyPressed->code == sf::Keyboard::Key::Enter)
		{
			RequestState(GameStateType::Playing);
		}
	}
}

void MainMenuStateData::Update(float deltaTime)
{

}

void MainMenuStateData::Draw(sf::RenderWindow& window)
{
	window.draw(m_startGameText);
	window.draw(m_hint);
}
