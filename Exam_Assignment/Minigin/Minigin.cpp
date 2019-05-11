#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"

// components
#include "BaseComponent.h"
#include "TextRendererComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"

// services
#include "ServiceLocator.h"

// audio
#include "Audio.h"
#include "NullAudio.h"
#include "GameAudio.h"

void dae::Minigin::Initialize()
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

	Renderer::GetInstance().Init(window);

	
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Adding background
	//auto pGameObject = new GameObject();
	//pGameObject->AddComponent(new TextureComponent(pGameObject));
	//pGameObject->GetComponent<TextureComponent>()->SetTexture("background.jpg");
	//scene.Add(pGameObject);

	// adding FPS counter
	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto pFPSObject = new GameObject;
	//pFPSObject->AddComponent(new TextRendererComponent("xxx", font, pFPSObject));
	//pFPSObject->AddComponent(new FPSComponent(pFPSObject));
	//scene.Add(pFPSObject);

	// services
	//ServiceLocator::GetInstance().Init();
	//ServiceLocator::GetInstance().RegisterAudioService(new GameAudio());
	//ServiceLocator::GetInstance().GetAudio().Init();
	// adding sound
	//ServiceLocator::GetInstance().GetAudio().AddSound("../Data/laser.ogg");

	// inputs
	//InputManager::GetInstance().ChangeCommand(ControllerButton::DpadL, 0, new MoveLeftCommand(pGameObject));
	//InputManager::GetInstance().ChangeCommand(ControllerButton::DpadR, 0, new MoveRightCommand(pGameObject));
	//InputManager::GetInstance().ChangeCommand(ControllerButton::DpadU, 0, new MoveUpCommand(pGameObject));
	//InputManager::GetInstance().ChangeCommand(ControllerButton::DpadD, 0, new MoveDownCommand(pGameObject));
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	
	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

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
