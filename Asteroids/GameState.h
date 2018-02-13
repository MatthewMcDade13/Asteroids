#pragma once

struct GameState
{
	enum GState
	{
		Menu,
		Playing,
		Paused
	};
private:
	GameState() = delete;
};
