#include "pch.h"
#include "LevelLoader.h"

using namespace dae;
std::vector<dae::GameObject*> dae::LevelLoader::loadLevel(Scene & sceneRef, std::string path)
{
	std::ifstream inputStream(path);     

	// get all the characters
	char character;
	while (inputStream.get(character))
	{
		switch (character)
		{
		// nothing
		case '0':
			// add empty gameobject 

			break;
		// Sno Bee
		case 'S':
			// add a sno bee enemy

			break;		
		// ice block
		case 'I':
			// add an ice block


			break;
		// diamond block
		case 'D':
			// add a diamond block

			break;	
		// egg block
		case 'E':
			// add an egg block
			break;
		// enter
		case 13:
			// do nothing, enter is for readability for the level editor person

			break;
		// non defined char, throw error
		default:
			throw;
			break;
		}
	}

	inputStream.close();
}
