#pragma once
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>

struct GameAudio
{
	GameAudio();
	sf::Music gameplayMusic;
	sf::Sound explodeSound;
	sf::Sound lazerSound;

	void muteAll();
	void unMuteAll();

	void muteSoundEffects();
	void unMuteSoundEffects();

	void muteMusic();
	void unMuteMusic();

	bool isMusicMuted() const;
	bool areEffectsMuted() const;

private:
	bool m_bMusicMuted;
	bool m_bEffectsMuted;
};

