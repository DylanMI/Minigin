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

		std::vector<GameObject*> loadLevel(Scene& sceneRef, std::string path);		
	};

}


