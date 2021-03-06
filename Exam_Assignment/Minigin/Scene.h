#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(SceneObject* object);
		void Remove(SceneObject* object);

		void ClearAll();

		void SetLevelIdx(int newIdx);
		int GetLevelIdx();

		void Update(const float& deltaTime);
		void Render() const;

		Scene();
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string mName{};
		std::vector<SceneObject*> mObjects{};

		int m_loadLevelIdx{};

		static unsigned int idCounter; 
	};

}
