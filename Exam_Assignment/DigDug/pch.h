
#ifndef PCH_H
#define PCH_H
#include "targetver.h"
#include <windows.h>
#include <vld.h>
#include "SDL.h"
#include "Minigin.h"

// TODO: add headers that you want to pre-compile here
#include <stdio.h>
#include <memory> // smart pointers
#include <map>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <thread>
#include "Structs.h"

#include "Scene.h"

// XInput
#pragma comment(lib, "XInput.lib") 
#include <XInput.h>

// components and objects
#include "GameObject.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#include "BaseCharacter.h"
#include "TextRendererComponent.h"
#include "FPSComponent.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "AnimatorComponent.h"
#include "AiComponent.h"
#include "CollisionComponent.h"
#include "CollisionCheckerComponent.h"
#include "RockComponent.h"
#include "StateComponent.h"
#include "PookaComponent.h"
#include "GunComponent.h"
#include "DeleteSelfComponent.h"


// services
#include "ServiceLocator.h"


// managers
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "CollisionManager.h"


// SDL 
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "SDL2_mixer.lib")  
#pragma comment(lib, "SDL2_image.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h> 

// audio
#include "Audio.h"
#include "NullAudio.h"
#include "GameAudio.h"


#endif //PCH_H
