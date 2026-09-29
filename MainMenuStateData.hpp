#pragma once
#include "GameStateData.hpp"
#include "GameConfig.hpp"

// Состояние главного меню, показывает пукнты главного меню и обработка перехода в Playing
class MainMenuStateData : public GameStateData
{
public:
	MainMenuStateData(const sf::Font& font); // КОнструктор текста
	
	void Init() override; // Положение элементов
	void HandleWindowEvent(const sf::Event& event) override; // Обработка Enter и запрос перехода в Playing
	void Update(float deltaTime) override; // Будут обновляться пункты меню
	void Draw(sf::RenderWindow& window) override; // Отрисовка элементов меню

private:
	sf::Text startGameText;
	sf::Text hint;
};