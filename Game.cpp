#include "Game.hpp"

Game::Game()
	: window(sf::VideoMode({ 800, 600 }), "Arcanoid"),
	board(sf::Vector2f{ 0.f, 0.f }, sf::Vector2f{ 800.f, 600.f }),
	platform(sf::Vector2f{ 375.f, 580.f }, sf::Vector2f{ 100.f, 10.f }, 100.f),
	ball(sf::Vector2f{ 395.f, 540.f }, sf::Vector2f{ 100.f, -100.f }, 5.f)
{
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

MoveDirection Game::GetMoveDirection() const
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		return MoveDirection::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		return MoveDirection::Right;
	}

	return MoveDirection::None;
}

void Game::Input()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
		else if (auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->code == sf::Keyboard::Key::Space)
			{
				ball.Launch();
			}
		}
	}
}

void Game::Update(float deltaTime)
{
	const MoveDirection direction = GetMoveDirection();

	platform.Update(board, deltaTime, direction);
	ball.AttachTo(platform.GetBounds());
	ball.Update(board, deltaTime);
	if (IsCollision(platform.GetBounds(), ball.GetBounds()))
	{
		ball.BounceFromPlatform();
	}

	const sf::FloatRect ballBounds = ball.GetBounds();
	const sf::FloatRect boardBounds = board.GetBounds();

	const float ballBottom = ballBounds.position.y + ballBounds.size.y;
	const float boardBottom = boardBounds.position.y + boardBounds.size.y;
	if (ballBottom >= boardBottom)
	{
		ball.Reset();
		ball.AttachTo(platform.GetBounds());
	}
}

void Game::Draw()
{
	window.clear();
	board.DrawBoard(window);
	platform.DrawPlatform(window);
	ball.DrawBall(window);
	window.display();
}
