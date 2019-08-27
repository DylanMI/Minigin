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

void Game::LoadSystems()
{
	using namespace dae;
	{
		mp_gameFieldGridObject = new dae::GameObject();
		gameObserver = new GameObserver(mp_gameFieldGridObject);

		// events
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_DIAMONDSCHAIN);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_EGGHATCHED);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_EGGSPAWNED);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_EGGDESTROYED);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_ENDGAME);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_ENEMYDIED);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_ENEMYSPAWNED);
		Messenger::GetInstance().Subscribe(gameObserver, Event::EVENT_PENGODIED);
	}

}

void Game::LoadGame(int identifier)
{
	using namespace dae;
	{
		// making the scene
		auto& m_scene = SceneManager::GetInstance().CreateScene("Pengo");

		switch (identifier)
		{
			// 0 == Menu
		case 0:
			break;
			// 1 == first level singleplayer
		case 1:
			mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 34,27,464,464 }, 13, 13, m_scene));
			m_scene.Add(mp_gameFieldGridObject);
			
			// loading the level
			LevelLoader::GetInstance().LoadLevel(m_scene, mp_gameFieldGridObject, gameObserver, "../Data/Map.txt");

			break;
			// 2 == second level singleplayer
		case 2:
			mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 34,27,464,464 }, 13, 13, m_scene));
			m_scene.Add(mp_gameFieldGridObject);

			// loading the level
			LevelLoader::GetInstance().LoadLevel(m_scene, mp_gameFieldGridObject, gameObserver, "../Data/Map2.txt");

			break;
			// 3 == first level co op
		case 3:
			mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 34,27,464,464 }, 13, 13, m_scene));
			m_scene.Add(mp_gameFieldGridObject);
			
			break;
			// 4 == second level co op
		case 4:
			mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 34,27,464,464 }, 13, 13, m_scene));
			m_scene.Add(mp_gameFieldGridObject);

			break;
			// 5 == first level VS
		case 5:
			mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 34,27,464,464 }, 13, 13, m_scene));
			m_scene.Add(mp_gameFieldGridObject);
			break;
			// 6 == second level VS
		case 6:

			mp_gameFieldGridObject->AddComponent(new dae::GameFieldGridComponent(mp_gameFieldGridObject, { 34,27,464,464 }, 13, 13, m_scene));
			m_scene.Add(mp_gameFieldGridObject);

			break;
		default:
			break;
		}
		if (identifier == 0) return;


		// adding UI
		//adding FPS counter
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
		auto mp_FPSObj = new dae::GameObject();
		mp_FPSObj->AddComponent(new TextRendererComponent("xxx", font, mp_FPSObj));
		mp_FPSObj->GetComponent<TextRendererComponent>()->SetPosition(570, 460);
		mp_FPSObj->AddComponent(new FPSComponent(mp_FPSObj));

		m_scene.Add(mp_FPSObj);

		// adding score
		auto mp_ScoreCounter = new dae::GameObject();
		mp_ScoreCounter->AddComponent(new TextRendererComponent("SCORE: 0", font, mp_ScoreCounter));
		// adding ScoreChecker Component
		mp_ScoreCounter->AddComponent(new UIScoreComponent(mp_ScoreCounter, gameObserver));
		mp_ScoreCounter->GetComponent<TextRendererComponent>()->SetPosition(500, 0);
		m_scene.Add(mp_ScoreCounter);

		// adding lives
		auto mp_liveCounter = new dae::GameObject();
		mp_liveCounter->AddComponent(new TextRendererComponent("LIVES: 0", font, mp_liveCounter));
		// adding ScoreChecker Component
		mp_liveCounter->AddComponent(new UILiveComponent(mp_liveCounter, gameObserver));
		mp_liveCounter->GetComponent<TextRendererComponent>()->SetPosition(500, 50);
		m_scene.Add(mp_liveCounter);
		
		// adding eggcounts
		auto mp_eggCounter = new dae::GameObject();
		mp_eggCounter->AddComponent(new TextRendererComponent("EGGS: 0", font, mp_eggCounter));
		// adding ScoreChecker Component
		mp_eggCounter->AddComponent(new UIEggComponent(mp_eggCounter, gameObserver));
		mp_eggCounter->GetComponent<TextRendererComponent>()->SetPosition(500, 100);
		m_scene.Add(mp_eggCounter);


	}
}



void Game::Run()
{
	// initialize window
	Initialize();

	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Data/");
	
	// Load the systems like events etc...
	LoadSystems();
	
	// load the menu
	LoadGame(1);


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
	delete gameObserver;
}