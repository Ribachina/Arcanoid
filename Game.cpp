#include "Game.hpp"
#include "GameConfig.hpp"

Game::Game()
	: window(sf::VideoMode({ GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT }), "Arcanoid"),
	font ("Resources/Fonts/PB Pixel.ttf")
{
	ChangeState(GameStateType::MainMenu);
}


void Game::Run()
{
	sf::Clock clock;
	float lastTime = clock.getElapsedTime().asSeconds();

	while (window.isOpen())
	{
		float currentTime = clock.getElapsedTime().asSeconds();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		Input();
		Update(deltaTime);
		Draw();
	}
}

void Game::Input()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}

		currentState->HandleWindowEvent(*event);
	}
}

void Game::Update(float deltaTime)
{
	currentState->Update(deltaTime);
	
	const GameStateType requestedState = currentState->GetRequestedState();
	if (requestedState != GameStateType::None)
	{
		ChangeState(requestedState);
	}
}

void Game::ChangeState(GameStateType type)
{
	switch (type)
	{
	case GameStateType::MainMenu:
		currentState = std::make_unique<MainMenuStateData>(font);
		break;
	
	case GameStateType::Playing:
		currentState = std::make_unique < PlayingStateData>();
		break;

	case GameStateType::Victory:
		currentState = std::make_unique < VictoryStateData>(font);
		break;

	case GameStateType::None:
		return;
	}

	currentState->Init();
}

void Game::Draw()
{
	window.clear();
	currentState->Draw(window);
	window.display();
}
