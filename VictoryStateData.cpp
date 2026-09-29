#include "VictoryStateData.hpp"

VictoryStateData::VictoryStateData(const sf::Font& font)
	:title(font, "YOU WIN", 80),
	question(font, "Restart?\nPress Y/N", 40)
{
}

void VictoryStateData::Init()
{
	title.setFillColor(sf::Color::Green);
	title.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(title), 140.f});
	
	question.setFillColor(sf::Color::White);
	question.setPosition(sf::Vector2f{ GameConfig::GetCenteredTextX(question), 280.f });
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
	window.draw(title);
	window.draw(question);
}
