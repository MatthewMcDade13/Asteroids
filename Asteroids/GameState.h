#pragma once

struct GameState
{
	enum GState
	{
		Menu,
		Playing,
		Paused,
		GameOver
	};
private:
	GameState() = delete;
};
