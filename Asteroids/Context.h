#pragma once

namespace pure
{
	struct ResourceHolder;
}

struct GameAudio;

struct Context
{
	pure::ResourceHolder* resources;
	GameAudio* audio;
};