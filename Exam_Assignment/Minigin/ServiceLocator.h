#pragma once
#include "Audio.h"
#include "Singleton.h"
#include "GameObject.h"
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

		static std::vector<GameObject*> GetCollisionObjects();
		static void RegisterCollisionObject(GameObject* object);
	private:
		static Audio* audioService;
		static std::vector<GameObject*> collisionObjects
	};
}
