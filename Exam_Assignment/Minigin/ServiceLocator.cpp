#include "MiniginPCH.h"
#include "ServiceLocator.h"

namespace dae
{
	Audio* ServiceLocator::audioService = nullptr;

	void dae::ServiceLocator::Init()
	{
		audioService = nullptr;
	}

	Audio & ServiceLocator::GetAudio()
	{
		return *audioService;
	}

	void dae::ServiceLocator::RegisterAudioService(Audio * service)
	{
		audioService = service;
	}

}

