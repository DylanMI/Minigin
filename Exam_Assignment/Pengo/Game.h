#pragma once
#include "Scene.h"


class Game
{
	const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* window{};
public:
	Game();
	~Game() = default;

	void Initialize();
	void LoadGame(int identifier);
	void LoadSystems();
	void Cleanup();
	void Run();


private:
	dae::GameObserver* gameObserver;
	dae::GameObject* mp_gameFieldGridObject;
	dae::Scene& m_scene;
};