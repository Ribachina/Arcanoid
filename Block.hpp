#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Drawable.hpp"
#include "Collidable.hpp"

// Ѕазовый класс разрушаемого блока
class Block : public Drawable, public Collidable
{
public:
	// —оздаЄм блок с позицей и размером
	Block(sf::Vector2f position, sf::Vector2f size);
	virtual ~Block() = default;
	

	void Draw(sf::RenderWindow& window) const override;
	sf::FloatRect GetBounds() const override;

	virtual bool OnHit(); // true - м€ч отскочил; false - прошЄл на сквозь
	bool IsDestroyed() const;

protected:
	void SetColor(sf::Color color);
	void SetOutline(sf::Color color, float thickness);
	void Destroy();

private:
	sf::RectangleShape m_rectangle;
	bool m_destroyed = false;
};