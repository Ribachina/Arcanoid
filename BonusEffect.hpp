#pragma once

// Паттерн Strategy для временного бонусного эффекта
class BonusEffect
{
public:
	virtual ~BonusEffect() = default;

	virtual void Apply() = 0; // Принимает модификатор
	virtual void Remove() = 0; // Выполняет обратное изменение
};