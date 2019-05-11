#include "MiniginPCH.h"
#include "ServiceLocator.h"

namespace dae
{
	Audio* ServiceLocator::audioService = nullptr;

	ServiceLocator::~ServiceLocator()
	{
		audioService = nullptr;
		delete audioService;
	}

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

