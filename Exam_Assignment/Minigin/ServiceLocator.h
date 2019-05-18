#pragma once
#include "Audio.h"
#include "Singleton.h"
#include "GameObject.h"
#include <vector>
class Audio;
class GameObject;
namespace dae
{
	class ServiceLocator final : public Singleton<ServiceLocator>
	{
	public:
		ServiceLocator() = default;
		~ServiceLocator();

		static void Init();
		static Audio& GetAudio();
		static void RegisterAudioService(Audio* service);

	private:
		static Audio* audioService;

	};
}
