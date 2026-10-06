#include "Game.hpp"
#include "GameConfig.hpp"

Game::Game()
	: m_window(sf::VideoMode({ GameConfig::WINDOW_WIDTH, GameConfig::WINDOW_HEIGHT }), "Arcanoid"),
	m_font ("Resources/Fonts/PB Pixel.ttf")
{
	ChangeState(GameStateType::MainMenu);
}


void Game::Run()
{
	sf::Clock clock;
	float lastTime = clock.getElapsedTime().asSeconds();

	while (m_window.isOpen())
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
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}

		m_currentState->HandleWindowEvent(*event);
	}
}

void Game::Update(float deltaTime)
{
	m_currentState->Update(deltaTime);
	
	const GameStateType requestedState = m_currentState->GetRequestedState();
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
		m_currentState = std::make_unique<MainMenuStateData>(m_font);
		break;
	
	case GameStateType::Playing:
		m_currentState = std::make_unique < PlayingStateData>();
		break;

	case GameStateType::Victory:
		m_currentState = std::make_unique < VictoryStateData>(m_font);
		break;

	case GameStateType::None:
		return;
	}

	m_currentState->Init();
}

void Game::Draw()
{
	m_window.clear();
	m_currentState->Draw(m_window);
	m_window.display();
}
