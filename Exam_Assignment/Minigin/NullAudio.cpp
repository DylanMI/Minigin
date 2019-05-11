#include "MiniginPCH.h"
#include "NullAudio.h"

void dae::NullAudio::Init()
{
}

int dae::NullAudio::AddSound(std::string filePath)
{
	return 0;
}

void dae::NullAudio::PlaySound(int /*soundID*/)
{
}

void dae::NullAudio::StopSound(int /*soundID*/)
{
}

void dae::NullAudio::StopAllSounds()
{
}
