#include "stdafx.h"
#include "GameAudio.h"


GameAudio::GameAudio():
	m_bEffectsMuted(false),
	m_bMusicMuted(false)
{
}

void GameAudio::muteAll()
{
	gameplayMusic.setVolume(0.f);
	explodeSound.setVolume(0.f);
	lazerSound.setVolume(0.f);
	m_bEffectsMuted = true;
	m_bMusicMuted = true;
}

void GameAudio::unMuteAll()
{
	gameplayMusic.setVolume(100.f);
	explodeSound.setVolume(100.f);
	lazerSound.setVolume(100.f);
	m_bEffectsMuted = false;
	m_bMusicMuted = false;
}

void GameAudio::muteSoundEffects()
{
	explodeSound.setVolume(0.f);
	lazerSound.setVolume(0.f);
	m_bEffectsMuted = true;
}

void GameAudio::unMuteSoundEffects()
{
	explodeSound.setVolume(100.f);
	lazerSound.setVolume(100.f);
	m_bEffectsMuted = false;
}

void GameAudio::muteMusic()
{
	gameplayMusic.setVolume(0.f);
	m_bMusicMuted = true;
}

void GameAudio::unMuteMusic()
{
	gameplayMusic.setVolume(100.f);
	m_bMusicMuted = false;
}

bool GameAudio::isMusicMuted() const
{
	return m_bMusicMuted;
}

bool GameAudio::areEffectsMuted() const
{
	return m_bEffectsMuted;
}
