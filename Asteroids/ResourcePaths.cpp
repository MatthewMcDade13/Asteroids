#include "stdafx.h"
#include "ResourcePaths.h"
#include "Constants.h"
#include <array>

using namespace std;
using namespace pure;

constexpr const char* paths[] = {
	"ARCADE_N.TTF",
	"explode.wav",
	"lazer_shoot.wav",
	"Space_Chase_Music.wav"
};

string getResourcePath(Resource resource)
{
	return paths[static_cast<uint32>(resource)];
}
