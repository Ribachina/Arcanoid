#include "MainMenuStateData.hpp"

MainMenuStateData::MainMenuStateData(const sf::Font& font)
	:startGameText(font, "Start Game", 40),
	hint(font, "Press Enter to start game", 30)
{
}

void MainMenuStateData::Init()
{
	startGameText.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(startGameText), 280.f });
	//startGameText.setFillColor(sf::Color::White);

	hint.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(hint), 550.f });
	//hint.setFillColor(sf::Color::White);
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
	window.draw(startGameText);
	window.draw(hint);
}
