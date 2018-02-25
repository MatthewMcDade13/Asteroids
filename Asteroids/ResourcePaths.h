#pragma once

#include <string>

enum class Resource : unsigned int 
{
	Font_Arcade = 0,
	Sound_Explode = 1,
	Sound_Lazer = 2,
	Music_Playing = 3
};

std::string getResourcePath(Resource resource);