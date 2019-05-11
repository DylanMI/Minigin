// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include <windows.h>
#include <vld.h>
#include "SDL.h"
#include "Minigin.h"

// TODO: add headers that you want to pre-compile here

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <tchar.h>
#include <memory> // smart pointers
#include <vector>
#include <chrono>
#include <thread>
#include "Structs.h"
#include "GameObject.h"
#include "Scene.h"

#include "Renderer.h"

// components
#include "BaseComponent.h"
#include "TextRendererComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"

// services
#include "ServiceLocator.h"

// SDL Sound implementation
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_mixer.lib")  
#include <SDL_mixer.h> 

// audio
#include "Audio.h"
#include "NullAudio.h"
#include "GameAudio.h"



#endif //PCH_H
