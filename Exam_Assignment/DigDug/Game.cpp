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

void Game::LoadGame() const
{
	using namespace dae;
	{
		// making the scene
		auto& m_scene = SceneManager::GetInstance().CreateScene("Demo");

		//Adding background
		//auto pGameObject = new dae::GameObject();
		//pGameObject->AddComponent(new TextureComponent(pGameObject));
		//pGameObject->GetComponent<TextureComponent>()->SetTexture("background.jpg");
		//m_scene.Add(pGameObject);

		// Adding the character
		auto mp_Character = new dae::BaseCharacter();
		mp_Character->AddComponent(new TextureComponent(mp_Character));
		mp_Character->AddComponent(new AnimatorComponent(mp_Character));
		mp_Character->GetComponent<AnimatorComponent>()->SetSpeed(1.0f);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::IDLE, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunLeft.png"), 16, 16, 2);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::LEFT, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunRight.png"), 16, 16, 2);
		mp_Character->AddComponent(new AiComponent(mp_Character));
		
		// setting the states
		mp_Character->GetComponent<AiComponent>()->AddTransition(mp_Character, State::IDLE, State::LEFT, new std::vector<bool>{true,true});
		mp_Character->GetComponent<AiComponent>()->AddTransition(mp_Character, State::LEFT, State::IDLE, new std::vector<bool>{true,true});
		

		mp_Character->SetPosition({ 50,50 });
		m_scene.Add(mp_Character);

		// //adding FPS counter
		//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		//auto mp_FPSObj = new dae::GameObject();
		//mp_FPSObj->AddComponent(new TextRendererComponent("xxx", font, mp_FPSObj));
		//mp_FPSObj->AddComponent(new FPSComponent(mp_FPSObj));
		//m_scene.Add(mp_FPSObj);






	}
}

void Game::Cleanup()
{

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
