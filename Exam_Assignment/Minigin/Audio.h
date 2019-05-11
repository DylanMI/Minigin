#pragma once
#include <iostream>
#include <vector>


namespace dae
{
	class Audio
	{
	public:
		virtual ~Audio() {}
		virtual void Init() = 0;
		virtual int AddSound(std::string filePath) = 0;
		virtual void PlaySound(int soundID) = 0;
		virtual void StopSound(int soundID) = 0;
		virtual void StopAllSounds() = 0;

	};
}


