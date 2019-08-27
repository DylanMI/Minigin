#include "pch.h"
#include "LevelLoader.h"

using namespace dae;
std::vector<dae::GameObject*> dae::LevelLoader::LoadLevel(Scene & sceneRef, GameObject* gameGridObj, GameObserver* gameObserver, std::string path)
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
			objects.push_back(new GameObject);
			Messenger::GetInstance().Notify(Event::EVENT_ENEMYSPAWNED, 0);
			// give components
			
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
			objects.push_back(new GameObject);
			// give components

			// -- texture
			objects.back()->AddComponent(new TextureComponent(objects.back()));
			objects.back()->GetComponent<TextureComponent>()->SetTexture("DiamondBlock.png");
			objects.back()->GetComponent<TextureComponent>()->SetWidthAndHeight(32, 32);
			objects.back()->GetComponent<TextureComponent>()->SetIsAnimated(false);

			// -- ice functionality				
			objects.back()->AddComponent(new IceBlockComponent(objects.back(), Point2f{ 32.0f,32.0f }, gameGridObj));
			objects.back()->GetComponent<IceBlockComponent>()->SetPosition(counter);
			objects.back()->GetComponent<IceBlockComponent>()->SetSpeed(6.0f);

			// -- Diamond functionality
			objects.back()->AddComponent(new DiamondBlockComponent(objects.back(), gameGridObj));

			// -- add a self destruct for future use
			objects.back()->AddComponent(new DeleteSelfComponent(objects.back(), sceneRef));

			// -- Giving the game grid the information
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].isObstacle = true;
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].isDiamondBlock = true;
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].object = objects.back();
			
			counter++;
			break;	
		// egg block
		case 'E':
			// add an egg block
			objects.push_back(new GameObject);
			// give components

			// -- texture
			objects.back()->AddComponent(new TextureComponent(objects.back()));
			objects.back()->GetComponent<TextureComponent>()->SetTexture("IceBlock.png");
			objects.back()->GetComponent<TextureComponent>()->SetWidthAndHeight(32, 32);
			objects.back()->GetComponent<TextureComponent>()->SetIsAnimated(false);

			// -- animator
			objects.back()->AddComponent(new AnimatorComponent(objects.back()));

			// -- ice functionality				
			objects.back()->AddComponent(new IceBlockComponent(objects.back(), Point2f{ 32.0f,32.0f }, gameGridObj));
			objects.back()->GetComponent<IceBlockComponent>()->SetPosition(counter);
			objects.back()->GetComponent<IceBlockComponent>()->SetSpeed(6.0f);

			// -- egg functionality
			objects.back()->AddComponent(new EggBlockComponent(objects.back(), gameGridObj, sceneRef));

			// -- adding a state for animation to just function
			objects.back()->AddComponent(new StateComponent(objects.back(), false));
			objects.back()->GetComponent<StateComponent>()->SetState(State::IDLE);

			// -- add a self destruct for future use
			objects.back()->AddComponent(new DeleteSelfComponent(objects.back(), sceneRef));

			// -- Giving the game grid the information
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].isObstacle = true;
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].isEggBlock = true;
			gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[counter].object = objects.back();

			gameGridObj->GetComponent<GameFieldGridComponent>()->addEggBlock(objects.back());

			counter++;
			break;

			//player one pengo
		case '1':
			// adding the player 
			objects.push_back(new GameObject);
			// -- adding the movement comp
			objects.back()->AddComponent(new dae::PlayerPengoMovementComponent(objects.back(), { 16,16 }, 3, gameGridObj, gameObserver));
			objects.back()->GetComponent<PlayerPengoMovementComponent>()->SetPosition(counter);
			objects.back()->GetComponent<PlayerPengoMovementComponent>()->SetStartIdx(counter);

			// -- adding the state component
			objects.back()->AddComponent(new StateComponent(objects.back(), true));

			// -- adding the texture comp
			objects.back()->AddComponent(new dae::TextureComponent(objects.back()));
			objects.back()->GetComponent<dae::TextureComponent>()->SetIsAnimated(true);

			// -- adding the animator
			objects.back()->AddComponent(new dae::AnimatorComponent(objects.back()));
			objects.back()->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkLeft.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkRight.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkDown.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_UP, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkUp.png"), 16, 16, 2);

			// adding the inputs [Controller]
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadL, 0, new MoveLeftCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadR, 0, new MoveRightCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadU, 0, new MoveUpCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadD, 0, new MoveDownCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::ButtonA, 0, new InteractCommand(objects.back()));

			// adding the inputs [Keyboard]
			InputManager::GetInstance().ChangeKeyboardCommand('W', new MoveUpCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('A', new MoveLeftCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('S', new MoveDownCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('D', new MoveRightCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('E', new InteractCommand(objects.back()));
			
			counter++;
			break;
			//player Two pengo
		case '2':
			// adding the player 
			objects.push_back(new GameObject);
			// -- adding the movement comp
			objects.back()->AddComponent(new dae::PlayerPengoMovementComponent(objects.back(), { 16,16 }, 3, gameGridObj, gameObserver));
			objects.back()->GetComponent<PlayerPengoMovementComponent>()->SetPosition(counter);
			objects.back()->GetComponent<PlayerPengoMovementComponent>()->SetStartIdx(counter);

			// -- adding the state component
			objects.back()->AddComponent(new StateComponent(objects.back(), true));

			// -- adding the texture comp
			objects.back()->AddComponent(new dae::TextureComponent(objects.back()));
			objects.back()->GetComponent<dae::TextureComponent>()->SetIsAnimated(true);

			// -- adding the animator
			objects.back()->AddComponent(new dae::AnimatorComponent(objects.back()));
			objects.back()->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkLeft.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkRight.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkDown.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_UP, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkUp.png"), 16, 16, 2);

			// adding the inputs [Controller]
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadL, 1, new MoveLeftCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadR, 1, new MoveRightCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadU, 1, new MoveUpCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadD, 1, new MoveDownCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::ButtonA, 1, new InteractCommand(objects.back()));

			// adding the inputs [Keyboard]
			InputManager::GetInstance().ChangeKeyboardCommand('I', new MoveUpCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('J', new MoveLeftCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('K', new MoveDownCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('L', new MoveRightCommandPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('O', new InteractCommand(objects.back()));
			counter++;
			break;

			//player Two snoBee
		
		case '3':
			// adding the player 
			Messenger::GetInstance().Notify(Event::EVENT_ENEMYSPAWNED, 0);
			objects.push_back(new GameObject);
			// -- adding the movement comp
			objects.back()->AddComponent(new dae::PlayerSnoMovementComponent(objects.back(), { 16,16 }, 3, gameGridObj, gameObserver));
			objects.back()->GetComponent<PlayerSnoMovementComponent>()->SetPosition(counter);
			objects.back()->GetComponent<PlayerSnoMovementComponent>()->SetStartIdx(counter);

			// -- adding the state component
			objects.back()->AddComponent(new StateComponent(objects.back(), true));

			// -- adding the texture comp
			objects.back()->AddComponent(new dae::TextureComponent(objects.back()));
			objects.back()->GetComponent<dae::TextureComponent>()->SetIsAnimated(true);

			// -- adding the animator
			objects.back()->AddComponent(new dae::AnimatorComponent(objects.back()));
			objects.back()->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkLeft.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkRight.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkDown.png"), 16, 16, 2);
			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_UP, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkUp.png"), 16, 16, 2);

			objects.back()->GetComponent<AnimatorComponent>()->AddAnimation(State::STRUGGLING, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeStruggle.png"), 16, 16, 2);

			// adding the inputs [Controller]
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadL, 1, new MoveLeftCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadR, 1, new MoveRightCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadU, 1, new MoveUpCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadD, 1, new MoveDownCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeCommand(dae::ControllerButton::ButtonA, 1, new InteractSnoCommand(objects.back()));

			// adding the inputs [Keyboard]
			InputManager::GetInstance().ChangeKeyboardCommand('I', new MoveUpCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('J', new MoveLeftCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('K', new MoveDownCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('L', new MoveRightCommandSnoPlayer(objects.back()));
			InputManager::GetInstance().ChangeKeyboardCommand('O', new InteractSnoCommand(objects.back()));
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

	// call needed functions for start of level
	// call the eggs
	gameGridObj->GetComponent<GameFieldGridComponent>()->ShowEggBlocks();

	return objects;
}
