#pragma once
class Game
{
	const int msPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* window{};
public:
	Game() = default;
	~Game() = default;

	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();

};

