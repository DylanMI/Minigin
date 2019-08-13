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
			
			// give components
			objects.push_back(new GameObject);
			// -- texture
			objects.back()->AddComponent(new TextureComponent(objects.back()));
			objects.back()->GetComponent<TextureComponent>()->SetIsAnimated(true);

			// -- animator
			objects.back()->AddComponent(new dae::AnimatorComponent(objects.back()));
			objects.back()->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);
			
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkLeft.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkRight.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkDown.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_UP, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkUp.png"), 16, 16, 2);

			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigLeft.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigRight.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigDown.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_UP, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigUp.png"), 16, 16, 2);

			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::STRUGGLING, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeStruggle.png"), 16, 16, 2);

		
			// -- brainnnz
			objects.back()->AddComponent(new StateComponent(objects.back(),false));
			
			objects.back()->AddComponent(new SnoBeeAIComponent(objects.back(), Point2f{ 16,16 }, 2.0f, gameGridObj));
			objects.back()->GetComponent<SnoBeeAIComponent>()->SetPosition(counter);
			
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
			objects.back()->GetComponent<IceBlockComponent>()->SetSpeed(6.0f);

			// -- add a self destruct for future use
			objects.back()->AddComponent(new DeleteSelfComponent(objects.back(), sceneRef));

			// -- Giving the game grid the information
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].isObstacle = true;
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].object = objects.back();

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
