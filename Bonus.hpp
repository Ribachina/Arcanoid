#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "BonusEffect.hpp"

enum class BonusState
{
	Falling,
	Active,
	Finished
};

enum class BonusType
{
	WidePlatform,
	SlowBall,
	FastPlatform
};

// Игровой бонус - владеет BonusEffect
class Bonus
{
public:
	Bonus(sf::Vector2f position, std::unique_ptr<BonusEffect> effect, float duration, BonusType type);

	void Update(float deltaTime); // Обновляет движение бонуса
	void Draw(sf::RenderWindow& window) const;

	sf::FloatRect GetBounds() const;

	void Activate(); // Активирует "Стратегию" только у падающего бонуса
	void Miss();
	void Cancel();

	bool IsFinished() const;

	BonusType GetType() const;
	bool IsActive() const;
	void RefreshDuration(); // Сбрасывает таймер активного эффекта
	void Discard();
	bool IsFalling() const;

private:
	sf::RectangleShape m_rectangle;

	std::unique_ptr<BonusEffect> m_effect;

	BonusState m_state = BonusState::Falling;
	BonusType m_type;

	float m_duration;
	float m_activeTime = 0.f;

	static constexpr float FALL_SPEED = 150.f;
	static constexpr sf::Vector2f SIZE{ 20.f, 20.f };
};