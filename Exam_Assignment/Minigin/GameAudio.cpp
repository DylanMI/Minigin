#include "MiniginPCH.h"
#include "GameAudio.h"

void dae::GameAudio::Init()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

int dae::GameAudio::AddSound(std::string filePath)
{
	m_pSounds.push_back(Mix_LoadWAV(filePath.c_str()));
	if (!m_pSounds[m_pSounds.size() - 1]) {
		throw std::runtime_error(std::string("Failed to load Sound: ") + Mix_GetError());
		// handle error
	}
	return int(m_pSounds.size() - 1);
}

void dae::GameAudio::PlaySound(int soundID)
{
	// play sound with console API
	Mix_PlayChannel(-1, m_pSounds[soundID], 1);
}

void dae::GameAudio::StopSound(int /*soundID*/)
{
	// stop sound with console API
}

void dae::GameAudio::StopAllSounds()
{
	// stop all sound with console API

}