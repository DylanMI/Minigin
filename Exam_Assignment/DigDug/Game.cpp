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
		auto& m_scene = SceneManager::GetInstance().CreateScene("Demo");
	
		// handling the entire observer system
		m_LifeObserver = new LifeObserver();
		m_ScoreObserver = new ScoreObserver();

		Messenger::GetInstance().Subscribe(m_LifeObserver, Event::EVENT_DIED);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONFIRSTLAYER_POOKA);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONSECONDLAYER_POOKA);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONTHIRDLAYER_POOKA);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONFOURTHLAYER_POOKA);

		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONFIRSTLAYER_FYGAR);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONSECONDLAYER_FYGAR);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONTHIRDLAYER_FYGAR);
		Messenger::GetInstance().Subscribe(m_ScoreObserver, Event::EVENT_DIEDONFOURTHLAYER_FYGAR);

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
				dae::GameObject* gridObject = new dae::GameObject();
				// give it the right position
				gridObject->SetPosition({ float(startLeftX + width * k),float(startLeftY - height * i) });

				// give it a texture component
				gridObject->AddComponent(new TextureComponent{ gridObject });

				// set it to the right texture
				if (i < (rows / 4) * 1)
				{
					// Red
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetWidthAndHeight(16, 16);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("RedLayer.png"));

				}
				else if (i < (rows / 4) * 2)
				{
					// Brown
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetWidthAndHeight(16, 16);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("BrownLayer.png"));
				}
				else if (i < (rows / 4) * 3)
				{
					// Orange 
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetWidthAndHeight(16, 16);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("OrangeLayer.png"));
				}
				else
				{
					// Yellow
					gridObject->GetComponent<TextureComponent>()->SetIsAnimated(false);
					gridObject->GetComponent<TextureComponent>()->SetWidthAndHeight(16, 16);
					gridObject->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("YellowLayer.png"));
				}


				// give it a collider component [and set the tag to destructable, and give it a dimension]
				gridObject->AddComponent(new CollisionComponent(gridObject));
				gridObject->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{width,height});
				gridObject->GetComponent<CollisionComponent>()->SetTag(collisionTag::Terrain);
				m_scene.Add(gridObject);
				CollisionManager::GetInstance().RegisterCollisionObject(gridObject);
			}
		}

#pragma region Rock_One
		// the rock
		auto mp_rock = new dae::GameObject();
		
		mp_rock->AddComponent(new TextureComponent(mp_rock));
		mp_rock->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Rock_One.png"));
		mp_rock->GetComponent<TextureComponent>()->SetWidthAndHeight(16, 16);
		
		// collision Checker
		mp_rock->AddComponent(new CollisionCheckerComponent(mp_rock));
		mp_rock->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new FallCommandRock(mp_rock), collisionTag::Nothing);
		mp_rock->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new BreakCommandRock(mp_rock), collisionTag::Terrain);
		mp_rock->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_rock->GetComponent<CollisionCheckerComponent>()->SetOffset({ 0,16 });

		// collision
		mp_rock->AddComponent(new CollisionComponent(mp_rock));
		mp_rock->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{16,16});
		mp_rock->GetComponent<CollisionComponent>()->SetTag(collisionTag::Rock);

		mp_rock->AddComponent(new RockComponent(mp_rock));
		mp_rock->GetComponent<RockComponent>()->SetFallSpeed(-50.0f);

		mp_rock->SetPosition({ 6*16, 11*16 });
		m_scene.Add(mp_rock);
		CollisionManager::GetInstance().RegisterCollisionObject(mp_rock);

		// the clearing of the rock
		auto mp_Clearer = new dae::GameObject();
		mp_Clearer->AddComponent(new CollisionCheckerComponent(mp_Clearer));
		mp_Clearer->AddComponent(new StateComponent(mp_Clearer, true));
		mp_Clearer->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_Clearer->SetPosition({ 6 * 16, 11 * 16 });
		m_scene.Add(mp_Clearer);

#pragma endregion
#pragma region Rock_Two
		// the rock
		auto mp_rock2 = new dae::GameObject();

		mp_rock2->AddComponent(new TextureComponent(mp_rock2));
		mp_rock2->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Rock_One.png"));
		mp_rock2->GetComponent<TextureComponent>()->SetWidthAndHeight(16, 16);

		// collision Checker
		mp_rock2->AddComponent(new CollisionCheckerComponent(mp_rock2));
		mp_rock2->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new FallCommandRock(mp_rock2), collisionTag::Nothing);
		mp_rock2->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new BreakCommandRock(mp_rock2), collisionTag::Terrain);
		mp_rock2->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_rock2->GetComponent<CollisionCheckerComponent>()->SetOffset({ 0,16 });

		// collision
		mp_rock2->AddComponent(new CollisionComponent(mp_rock2));
		mp_rock2->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{ 16,16 });
		mp_rock2->GetComponent<CollisionComponent>()->SetTag(collisionTag::Rock);

		mp_rock2->AddComponent(new RockComponent(mp_rock2));
		mp_rock2->GetComponent<RockComponent>()->SetFallSpeed(-50.0f);

		mp_rock2->SetPosition({ 18 * 16, 11 * 16 });
		m_scene.Add(mp_rock2);
		CollisionManager::GetInstance().RegisterCollisionObject(mp_rock2);

		// the clearing of the rock
		auto mp_ClearerRock2 = new dae::GameObject();
		mp_ClearerRock2->AddComponent(new CollisionCheckerComponent(mp_ClearerRock2));
		mp_ClearerRock2->AddComponent(new StateComponent(mp_ClearerRock2, true));
		mp_ClearerRock2->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_ClearerRock2->SetPosition({ 18 * 16, 11 * 16 });
		m_scene.Add(mp_ClearerRock2);

#pragma endregion
#pragma region Pooka_One
		// pooka
		auto mp_Pooka = new dae::GameObject();
		mp_Pooka->SetSpeed(50.0f);
		mp_Pooka->AddComponent(new StateComponent(mp_Pooka, false));
		mp_Pooka->AddComponent(new ClampComponent(mp_Pooka));
		mp_Pooka->GetComponent<ClampComponent>()->SetClampRect(Rectf{ 0,100,640,380 });
		
		// texture
		mp_Pooka->AddComponent(new TextureComponent(mp_Pooka));
		mp_Pooka->GetComponent<TextureComponent>()->SetIsAnimated(true);

		// animator
		mp_Pooka->AddComponent(new AnimatorComponent(mp_Pooka));
		mp_Pooka->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);

		// pooka AI
		mp_Pooka->AddComponent(new PookaComponent(mp_Pooka));

		// collision checker
		mp_Pooka->AddComponent(new CollisionCheckerComponent(mp_Pooka));
		mp_Pooka->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_Pooka->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new RandomizeDirectionCommandEnemy(mp_Pooka), collisionTag::Terrain);
		mp_Pooka->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new HitByBlowerPooka(mp_Pooka), collisionTag::Blowgun);
		mp_Pooka->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new HitByRock(mp_Pooka), collisionTag::Rock);

		// colission
		mp_Pooka->AddComponent(new CollisionComponent(mp_Pooka));
		mp_Pooka->GetComponent<CollisionComponent>()->SetTag(collisionTag::Pooka);
		mp_Pooka->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{16,16});
		CollisionManager::GetInstance().RegisterCollisionObject(mp_Pooka);

		// animator
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::LEFT, dae::ResourceManager::GetInstance().LoadTexture("PookaRunLeft.png"), 16, 16, 2);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::RIGHT, dae::ResourceManager::GetInstance().LoadTexture("PookaRunRight.png"), 16, 16, 2);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::UP, dae::ResourceManager::GetInstance().LoadTexture("PookaRunUp.png"), 16, 16, 2);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::DOWN, dae::ResourceManager::GetInstance().LoadTexture("PookaRunDown.png"), 16, 16, 2);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::GHOSTING, dae::ResourceManager::GetInstance().LoadTexture("PookaGhost.png"), 8, 12, 2);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_1, dae::ResourceManager::GetInstance().LoadTexture("PookahInflate1.png"), 16, 16, 1);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_2, dae::ResourceManager::GetInstance().LoadTexture("PookaInflate2.png"), 16, 16, 1);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_3, dae::ResourceManager::GetInstance().LoadTexture("PookaInflate3.png"), 20, 21, 1);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_4, dae::ResourceManager::GetInstance().LoadTexture("PookaInflate4.png"), 20, 25, 1);
		mp_Pooka->GetComponent<AnimatorComponent>()->AddAnimation(State::CAUGHTBYROCK, dae::ResourceManager::GetInstance().LoadTexture("PookahInflate1.png"), 16, 16, 1);
		// finite state machine
		mp_Pooka->AddComponent(new AiComponent(mp_Pooka));
		mp_Pooka->GetComponent<AiComponent>()->AddTransition(mp_Pooka, State::GHOSTING, State::WANDERING, 
			{mp_Pooka->GetComponent<PookaComponent>()->GetToGhostState()}
		);
		mp_Pooka->GetComponent<AiComponent>()->AddTransition(mp_Pooka, State::WANDERING, State::GHOSTING,
			{ mp_Pooka->GetComponent<PookaComponent>()->GetToWanderingState() }
		);
		mp_Pooka->GetComponent<AiComponent>()->AddTransition(mp_Pooka, State::WANDERING, State::BLOW_1,
			{ (mp_Pooka->GetComponent<PookaComponent>()->GetIsNotInflated()) }
		);
		mp_Pooka->GetComponent<AiComponent>()->AddTransition(mp_Pooka, State::BLOW_1, State::WANDERING,
			{ (mp_Pooka->GetComponent<PookaComponent>()->GetIsInflated()) }
		);
		
		mp_Pooka->SetPosition({ 9 * 16, 25 * 16 });

		mp_Pooka->AddComponent(new DeleteSelfComponent(mp_Pooka,m_scene));
		m_scene.Add(mp_Pooka);

		// the clearing of the pooka
		auto mp_Clearer2 = new dae::GameObject();
		mp_Clearer2->AddComponent(new CollisionCheckerComponent(mp_Clearer2));
		mp_Clearer2->AddComponent(new StateComponent(mp_Clearer2, true));
		mp_Clearer2->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16*5,16*3 });
		mp_Clearer2->SetPosition({ 8 * 16, 26 * 16 });
		m_scene.Add(mp_Clearer2);
#pragma endregion
#pragma region Fygar_One
		// Fygar
		auto mp_Fygar = new dae::GameObject();
		mp_Fygar->SetSpeed(50.0f);
		mp_Fygar->AddComponent(new StateComponent(mp_Fygar, false));
		mp_Fygar->AddComponent(new ClampComponent(mp_Fygar));
		mp_Fygar->GetComponent<ClampComponent>()->SetClampRect(Rectf{ 0,100,640,380 });
		// texture
		mp_Fygar->AddComponent(new TextureComponent(mp_Fygar));
		mp_Fygar->GetComponent<TextureComponent>()->SetIsAnimated(true);

		// animator
		mp_Fygar->AddComponent(new AnimatorComponent(mp_Fygar));
		mp_Fygar->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);

		// Fygar AI
		mp_Fygar->AddComponent(new FygarComponent(mp_Fygar));

		// collision checker
		mp_Fygar->AddComponent(new CollisionCheckerComponent(mp_Fygar));
		mp_Fygar->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });
		mp_Fygar->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new RandomizeDirectionCommandEnemy(mp_Fygar), collisionTag::Terrain);
		mp_Fygar->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new HitByBlowerFygar(mp_Fygar), collisionTag::Blowgun);
		mp_Fygar->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new HitByRock(mp_Fygar), collisionTag::Rock);

		// colission
		mp_Fygar->AddComponent(new CollisionComponent(mp_Fygar));
		mp_Fygar->GetComponent<CollisionComponent>()->SetTag(collisionTag::Fugar);
		mp_Fygar->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{ 16,16 });
		CollisionManager::GetInstance().RegisterCollisionObject(mp_Fygar);

		// animator
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::LEFT, dae::ResourceManager::GetInstance().LoadTexture("FygarRunLeft.png"), 14, 14, 2);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::RIGHT, dae::ResourceManager::GetInstance().LoadTexture("FygarRunRight.png"), 14, 14, 2);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::UP, dae::ResourceManager::GetInstance().LoadTexture("FygarRunUp.png"), 14, 14, 2);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::DOWN, dae::ResourceManager::GetInstance().LoadTexture("FygarRunDown.png"), 14, 14, 2);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::GHOSTING, dae::ResourceManager::GetInstance().LoadTexture("FygarGhost.png"), 11, 13, 2);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_1, dae::ResourceManager::GetInstance().LoadTexture("FygarInflate1.png"), 16, 16, 1);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_2, dae::ResourceManager::GetInstance().LoadTexture("FygarInflate2.png"), 16, 16, 1);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_3, dae::ResourceManager::GetInstance().LoadTexture("FygarInflate3.png"), 20, 21, 1);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::BLOW_4, dae::ResourceManager::GetInstance().LoadTexture("FygarInflate1.png"), 20, 25, 1);
		mp_Fygar->GetComponent<AnimatorComponent>()->AddAnimation(State::CAUGHTBYROCK, dae::ResourceManager::GetInstance().LoadTexture("FygarInflate1.png"), 16, 16, 1);
		// finite state machine
		mp_Fygar->AddComponent(new AiComponent(mp_Fygar));
		mp_Fygar->GetComponent<AiComponent>()->AddTransition(mp_Fygar, State::GHOSTING, State::WANDERING,
			{ mp_Fygar->GetComponent<FygarComponent>()->GetToGhostState() }
		);
		mp_Fygar->GetComponent<AiComponent>()->AddTransition(mp_Fygar, State::WANDERING, State::GHOSTING,
			{ mp_Fygar->GetComponent<FygarComponent>()->GetToWanderingState() }
		);
		mp_Fygar->GetComponent<AiComponent>()->AddTransition(mp_Fygar, State::WANDERING, State::SHOOTING,
			{ mp_Fygar->GetComponent<FygarComponent>()->GetToWanderingState() }
		);
		mp_Fygar->GetComponent<AiComponent>()->AddTransition(mp_Fygar, State::SHOOTING, State::WANDERING,
			{ mp_Fygar->GetComponent<FygarComponent>()->GetToShootState() }
		);
		mp_Fygar->GetComponent<AiComponent>()->AddTransition(mp_Fygar, State::WANDERING, State::BLOW_1,
			{ (mp_Fygar->GetComponent<FygarComponent>()->GetIsNotInflated()) }
		);
		mp_Fygar->GetComponent<AiComponent>()->AddTransition(mp_Fygar, State::BLOW_1, State::WANDERING,
			{ (mp_Fygar->GetComponent<FygarComponent>()->GetIsInflated()) }
		);

		// the fygar gun
		mp_Fygar->AddComponent(new FygarGunComponent(mp_Fygar,m_scene));

		mp_Fygar->SetPosition({ 25 * 16, 25 * 16 });

		mp_Fygar->AddComponent(new DeleteSelfComponent(mp_Fygar, m_scene));
		m_scene.Add(mp_Fygar);

		// clearing of the fygar
		// the clearing of the pooka
		auto mp_Clearer3 = new dae::GameObject();
		mp_Clearer3->AddComponent(new CollisionCheckerComponent(mp_Clearer3));
		mp_Clearer3->AddComponent(new StateComponent(mp_Clearer3, true));
		mp_Clearer3->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16 * 5,16 * 3 });
		mp_Clearer3->SetPosition({ 25 * 16, 26 * 16 });
		m_scene.Add(mp_Clearer3);
#pragma endregion
#pragma region Character
		// Adding the character
		auto mp_Character = new dae::GameObject();
		mp_Character->SetSpeed(100.0f);
		mp_Character->SetPosition(Point2f{ 20 * 16 ,15 * 16 + 2 });
		mp_Character->AddComponent(new StateComponent(mp_Character, true));
		mp_Character->AddComponent(new ClampComponent(mp_Character));
		mp_Character->GetComponent<ClampComponent>()->SetClampRect(Rectf{ 0,51,640,380 });

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
		mp_Character->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new PlayerHitEnemy(mp_Character), collisionTag::Pooka);
		mp_Character->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new PlayerHitEnemy(mp_Character), collisionTag::Fugar);
		mp_Character->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new PlayerHitEnemy(mp_Character), collisionTag::Fire);
		mp_Character->GetComponent<CollisionCheckerComponent>()->addCollisionEvent(new PlayerHitRock(mp_Character), collisionTag::Rock);
		m_scene.Add(mp_Character);

		// shooter
		mp_Character->AddComponent(new GunComponent(mp_Character, m_scene));

		// the clearing of the Player
		auto mp_ClearerPlayer = new dae::GameObject();
		mp_ClearerPlayer->AddComponent(new CollisionCheckerComponent(mp_ClearerPlayer));
		mp_ClearerPlayer->AddComponent(new StateComponent(mp_ClearerPlayer, true));
		mp_ClearerPlayer->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 3*16,12*16 });
		mp_ClearerPlayer->SetPosition({ 20 * 16, 16 * 16 });
		m_scene.Add(mp_ClearerPlayer);
		
#pragma endregion

		// adding the character as a target
		mp_Pooka->GetComponent<PookaComponent>()->SetTarget(mp_Character);
		mp_Fygar->GetComponent<FygarComponent>()->SetTarget(mp_Character);

		// fixing the inputs 
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadU, 1, new MoveUpCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadL, 1, new MoveLeftCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadR, 1, new MoveRightCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::DpadD, 1, new MoveDownCommandPlayer(mp_Character));
		InputManager::GetInstance().ChangeCommand(dae::ControllerButton::ButtonA, 1, new ShootCommandPlayer(mp_Character));

		//adding FPS counter
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		auto mp_FPSObj = new dae::GameObject();
		mp_FPSObj->AddComponent(new TextRendererComponent("xxx", font, mp_FPSObj));
		mp_FPSObj->AddComponent(new FPSComponent(mp_FPSObj));
		m_scene.Add(mp_FPSObj);

		// adding the life counter
		auto mp_LifeCounter = new dae::GameObject();
		mp_LifeCounter->AddComponent(new TextRendererComponent("LIVES: 3", font, mp_LifeCounter));
		// adding LifeChecker Component
		mp_LifeCounter->AddComponent(new LifeComponent(mp_LifeCounter, m_LifeObserver));
		mp_LifeCounter->GetComponent<TextRendererComponent>()->SetPosition(400, 50);
		m_scene.Add(mp_LifeCounter);


		// adding the score counter
		auto mp_ScoreCounter = new dae::GameObject();
		mp_ScoreCounter->AddComponent(new TextRendererComponent("SCORE: 0", font, mp_ScoreCounter));
		// adding ScoreChecker Component
		mp_ScoreCounter->AddComponent(new ScoreComponent(mp_ScoreCounter, m_ScoreObserver));
		mp_ScoreCounter->GetComponent<TextRendererComponent>()->SetPosition(400,0);
		m_scene.Add(mp_ScoreCounter);


	}
}

void Game::Cleanup()
{
	delete m_LifeObserver;
	delete m_ScoreObserver;

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

			doContinue = input.ProcessInput(deltaTime) && !m_LifeObserver->GetIsDead();
			sceneManager.Update(deltaTime);
			renderer.Render();

			lastTime = currentTime;
			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
			
		}
	}

	Cleanup();
}






