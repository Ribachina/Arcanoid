#pragma once

// Перечисление возможных состояний игры
// None означает, что переход в другое состояние не запрашивали

enum class GameStateType
{
	None,
	MainMenu,
	Playing,
	Victory
};