#pragma once
#include <SFML/Graphics.hpp>

bool IsCollision(const sf::FloatRect& first, const sf::FloatRect& second); // Проверка коллизий (2-х любых прямоугольников)