#include "pch.h"
#include "Game.h"


void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	dae::Renderer::GetInstance().Init(window);


}

void Game::LoadGame()
{
	using namespace dae;
	{
		// making the scene
		auto& m_scene = SceneManager::GetInstance().CreateScene("Pengo");

		// adding the gameFieldGrid
		auto mp_gameFieldGridObject = new dae::GameObject();
		mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 96,34,464,464 }, 13, 13, m_scene));
		m_scene.Add(mp_gameFieldGridObject);
		
		// loading the level
		LevelLoader::GetInstance().loadLevel(m_scene,mp_gameFieldGridObject,"../Data/Map.txt");
			
		// adding the player 
		auto mp_PlayerPengo = new dae::GameObject();
		
		// -- adding the movement comp
		mp_PlayerPengo->AddComponent(new dae::PlayerPengoMovementComponent(mp_PlayerPengo, { 16,16 }, 3, mp_gameFieldGridObject));
		mp_PlayerPengo->GetComponent<PlayerPengoMovementComponent>()->SetPosition(0);

		// -- adding the state component
		mp_PlayerPengo->AddComponent(new StateComponent(mp_PlayerPengo,true));

		// -- adding the texture comp
		mp_PlayerPengo->AddComponent(new dae::TextureComponent(mp_PlayerPengo));
		mp_PlayerPengo->GetComponent<dae::TextureComponent>()->SetIsAnimated(true);
		
		// -- adding the animator
		mp_PlayerPengo->AddComponent(new dae::AnimatorComponent(mp_PlayerPengo));
		mp_PlayerPengo->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);
		mp_PlayerPengo->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkLeft.png"), 16, 16, 2);
		mp_PlayerPengo->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkRight.png"), 16, 16, 2);
		mp_PlayerPengo->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkDown.png"), 16, 16, 2);
		mp_PlayerPengo->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_UP, dae::ResourceManager::GetInstance().LoadTexture("RedPengoWalkUp.png"), 16, 16, 2);
		
		m_scene.Add(mp_PlayerPengo);
		
		// adding the inputs
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadL, 1, new MoveLeftCommandPlayer(mp_PlayerPengo));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadR, 1, new MoveRightCommandPlayer(mp_PlayerPengo));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadU, 1, new MoveUpCommandPlayer(mp_PlayerPengo));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadD, 1, new MoveDownCommandPlayer(mp_PlayerPengo));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::ButtonA, 1, new InteractCommand(mp_PlayerPengo));
		
		// adding UI
		//adding FPS counter
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto mp_FPSObj = new dae::GameObject();
		mp_FPSObj->AddComponent(new TextRendererComponent("xxx", font, mp_FPSObj));
		mp_FPSObj->AddComponent(new FPSComponent(mp_FPSObj));

		m_scene.Add(mp_FPSObj);



	}
}

void Game::Run()
{
	// initialize window
	Initialize();

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");

	// load the entire game
	LoadGame();

	// update loop
	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = dae::Renderer::GetInstance();
		auto& sceneManager = dae::SceneManager::GetInstance();
		auto& input = dae::InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();

		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();

			doContinue = input.ProcessInput(deltaTime);
			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);

		}
	}

	Cleanup();
}


void Game::Cleanup()
{

}