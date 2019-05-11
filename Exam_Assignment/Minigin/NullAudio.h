#pragma once
#include "Audio.h"

namespace dae
{
	class NullAudio : public Audio
	{
	public:
		NullAudio() = default;
		~NullAudio() = default;

		virtual void Init() override;
		virtual int AddSound(std::string filePath) override;
		virtual void PlaySound(int soundID) override;
		virtual void StopSound(int soundID) override;
		virtual void StopAllSounds() override;
	};

}

