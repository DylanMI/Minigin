#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void Update(const float& deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
	};

}
