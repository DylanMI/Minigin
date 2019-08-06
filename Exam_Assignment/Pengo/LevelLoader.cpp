#include "pch.h"
#include "LevelLoader.h"

using namespace dae;
std::vector<dae::GameObject*> dae::LevelLoader::loadLevel(Scene & sceneRef, GameObject* gameGridObj, std::string path)
{
	int counter{};
	std::vector<dae::GameObject*> objects;
	std::ifstream inputStream(path);     

	// get all the characters
	char character;
	while (inputStream.get(character))
	{
		switch (character)
		{
		// nothing
		case '0':
			counter++;
			break;
		// Sno Bee
		case 'S':
			// add a sno bee enemy
			counter++;
			break;		
		// ice block
		case 'I':
			// add an ice block
			objects.push_back(new GameObject);
			// give components
			
			// -- texture
			objects.back()->AddComponent(new TextureComponent(objects.back()));
			objects.back()->GetComponent<TextureComponent>()->SetTexture("IceBlock.png");
			objects.back()->GetComponent<TextureComponent>()->SetWidthAndHeight(32, 32);
			objects.back()->GetComponent<TextureComponent>()->SetIsAnimated(false);
		
			// -- ice functionality				
			objects.back()->AddComponent(new IceBlockComponent(objects.back(), Point2f{ 32.0f,32.0f }, gameGridObj));
			objects.back()->GetComponent<IceBlockComponent>()->SetPosition(counter);

			counter++;
			break;
		// diamond block
		case 'D':
			// add a diamond block
			counter++;
			break;	
		// egg block
		case 'E':
			// add an egg block
			counter++;
			break;
		// enter
		case 13:
			// do nothing, enter is for readability for the level editor person

			break;
		// non defined char, throw error
		default:
			// do nothing
			break;
		}
	}

	for (int i{}; i < objects.size(); i++)
	{
		sceneRef.Add(objects[i]);
	}

	inputStream.close();
	return objects;
}
