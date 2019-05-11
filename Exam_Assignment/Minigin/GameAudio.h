#pragma once
#include "Audio.h"


namespace dae
{
	class GameAudio : public Audio
	{
	public:
		virtual ~GameAudio() {}
		virtual void Init() override;
		virtual int AddSound(std::string filePath) override;
		virtual void PlaySound(int soundID) override;
		virtual void StopSound(int soundID) override;
		virtual void StopAllSounds() override;

	private:
		std::vector<Mix_Chunk*> m_pSounds;
	};
}
