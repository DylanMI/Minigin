#pragma once
#include "Singleton.h"
#include <fstream>  

namespace dae
{
	class LevelLoader : public Singleton<LevelLoader>
	{
	public:
		LevelLoader() = default;
		~LevelLoader() = default;

		std::vector<GameObject*> LoadLevel(Scene& sceneRef,GameObject* gameGridObj, std::string path);		
	};

}


