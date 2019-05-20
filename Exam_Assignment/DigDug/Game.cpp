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

		// making the grid
		const int rows{ 25 };
		const int collumns{ 42 };
		const int startLeftX{ 0 };
		const int startLeftY{ 480 };
		
		const int width{ 16 };
		const int height{ 16 };

		const int ScreenWidth{ 640 };
		const int screenHeight{ 480 };

		// making the grid
		// for each row
		for (int i{}; i < rows ; i++)
		{
			// every collumn
			for (int k{}; k < collumns; k++)
			{
				// game a gameobject
				dae::GameObject* gridObject = new dae::GameObject;
				// give it the right position
				gridObject->SetPosition({ float(startLeftX + width * k),float(startLeftY - height * i) });

				// give it a texture component
				gridObject->AddComponent(new TextureComponent{ gridObject });

				// set it to the right texture
				if (i < (rows / 4) * 1)
				{
					// Red
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("RedLayer.png"));

				}
				else if (i < (rows / 4) * 2)
				{
					// Brown
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("BrownLayer.png"));
				}
				else if (i < (rows / 4) * 3)
				{
					// Orange 
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("OrangeLayer.png"));
				}
				else
				{
					// Yellow
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("YellowLayer.png"));
				}


				// give it a collider component [and set the tag to destructable, and give it a dimension]
				gridObject->AddComponent(new CollisionComponent(gridObject));
				Rectf Body{
					float(startLeftX + width * k),
					float(startLeftY - height * i),
					width,
					height
						  };

				gridObject->GetComponent<CollisionComponent>()->SetBody(Body);
				gridObject->GetComponent<CollisionComponent>()->SetTag(collisionTag::Terrain);
				m_scene.Add(gridObject);
				CollisionManager::GetInstance().RegisterCollisionObject(gridObject);
			}
		}

		// the rock
		auto mp_rock = new dae::GameObject();
		
		mp_rock->AddComponent(new TextureComponent(mp_rock));
		mp_rock->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Rock_One.png"));
		
		mp_rock->AddComponent(new CollisionCheckerComponent(mp_rock));
		mp_rock->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new FallCommandRock(mp_rock), collisionTag::Nothing);
		mp_rock->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new BreakCommandRock(mp_rock), collisionTag::Terrain);
		mp_rock->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_rock->GetComponent<CollisionCheckerComponent>()->SetOffset({ 0,16 });

		mp_rock->AddComponent(new RockComponent(mp_rock));
		mp_rock->GetComponent<RockComponent>()->SetFallSpeed(-50.0f);

		mp_rock->SetPosition({ 6*16, 10*16 });
		m_scene.Add(mp_rock);

		// the clearing of the rock
		auto mp_Clearer = new dae::GameObject();
		mp_Clearer->AddComponent(new CollisionCheckerComponent(mp_Clearer));
		mp_Clearer->AddComponent(new StateComponent(mp_Clearer, true));
		mp_Clearer->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_Clearer->SetPosition({ 6 * 16, 10 * 16 });
		m_scene.Add(mp_Clearer);

		// pooka
		auto mp_Pooka = new dae::GameObject();
		mp_Pooka->SetSpeed(50.0f);
		mp_Pooka->AddComponent(new StateComponent(mp_Pooka, false));

		// texture
		mp_Pooka->AddComponent(new TextureComponent(mp_Pooka));
		mp_Pooka->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("FygarInflate4.png"));
		
		//mp_Pooka->GetComponent<TextureComponent>()->SetIsAnimated(true);

		// animator
		//mp_Pooka->AddComponent(new AnimatorComponent(mp_Pooka));
		//mp_Pooka->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);

		mp_Pooka->AddComponent(new PookaComponent(mp_Pooka));

		// collision checker
		mp_Pooka->AddComponent(new CollisionCheckerComponent(mp_Pooka));
		mp_Pooka->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_Pooka->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new RandomizeDirectionCommandEnemy(mp_Pooka), collisionTag::Terrain);
		
		
		mp_Pooka->SetPosition({ 8 * 16, 26 * 16 });
		m_scene.Add(mp_Pooka);


		// the clearing of the pooka


		// Adding the character
		auto mp_Character = new dae::GameObject();
		mp_Character->SetSpeed(100.0f);
		mp_Character->AddComponent(new StateComponent(mp_Character, true));

		// texture
		mp_Character->AddComponent(new TextureComponent(mp_Character));
		mp_Character->GetComponent<TextureComponent>()->SetIsAnimated(true);

		// animator
		mp_Character->AddComponent(new AnimatorComponent(mp_Character));
		mp_Character->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::IDLE, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunLeft.png"), 16, 16, 2);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::LEFT, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunLeft.png"), 16, 16, 2);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::RIGHT, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunRight.png"), 16, 16, 2);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::UP, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunUp.png"), 16, 16, 2);
		mp_Character->GetComponent<AnimatorComponent>()->AddAnimation(State::DOWN, dae::ResourceManager::GetInstance().LoadTexture("DigDugRunDown.png"), 16, 16, 2);

		// collision checker
		mp_Character->AddComponent(new CollisionCheckerComponent(mp_Character));
		mp_Character->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		m_scene.Add(mp_Character);

		// fixing the inputs 
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadU, 1, new MoveUpCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadL, 1, new MoveLeftCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadR, 1, new MoveRightCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadD, 1, new MoveDownCommandPlayer(mp_Character));

		// //adding FPS counter
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto mp_FPSObj = new dae::GameObject();
		mp_FPSObj->AddComponent(new TextRendererComponent("xxx", font, mp_FPSObj));
		mp_FPSObj->AddComponent(new FPSComponent(mp_FPSObj));
		m_scene.Add(mp_FPSObj);

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
