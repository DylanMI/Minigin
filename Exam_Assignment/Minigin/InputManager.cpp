#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
	// nullptr the pointers and delete the pointer aftwards
	for (int i{}, s = m_MAXammControllers; i < s; i++)
	{
		delete aBtnCommand[i];
		delete bBtnCommand[i];
		delete xBtnCommand[i];
		delete yBtnCommand[i];
		delete padlBtnCommand[i];
		delete padrBtnCommand[i];
		delete paduBtnCommand[i];
		delete paddBtnCommand[i];
	}
	for (int k{}; k < m_MAXKeyboardAsciiSize; k++)
	{
		delete keyboardCommands[k].command;
	}
}
bool dae::InputManager::ProcessInput(float deltatime)
{

	// handle Controllers
	for (int i{0}; i < m_MAXammControllers; i++)
	{
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(i, &currentState);
		
		if (IsPressed(ControllerButton::ButtonA))
		{
			if (aBtnCommand[i] != nullptr) aBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::ButtonB))
		{
			if (bBtnCommand[i] != nullptr) bBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::ButtonX))
		{
			if (xBtnCommand[i] != nullptr) xBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::ButtonY))
		{
			if (yBtnCommand[i] != nullptr) yBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::DpadL))
		{
			if (padlBtnCommand[i] != nullptr) padlBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::DpadR))
		{
			if (padrBtnCommand[i] != nullptr) padrBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::DpadU))
		{
			if (paduBtnCommand[i] != nullptr) paduBtnCommand[i]->Execute(deltatime);
		}
		if (IsPressed(ControllerButton::DpadD))
		{
			if (paddBtnCommand[i] != nullptr) paddBtnCommand[i]->Execute(deltatime);
		}
	}	

	// handle keyboard events
	char character;
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		auto key = ev.key.keysym.sym;

		switch (ev.type)
		{
		case SDL_QUIT:
			return false;
		
		case SDL_KEYDOWN:
			character = *SDL_GetKeyName(key);
			if (int(character) > m_MAXKeyboardAsciiSize) return true;
			keyboardCommands[int(character)].isPressed = true;
			break;

		case SDL_KEYUP:
			character = *SDL_GetKeyName(key);
			if (int(character) > m_MAXKeyboardAsciiSize) return true;
			keyboardCommands[int(character)].isPressed = false;
			break;
		}
	}

	// handle the commands
	for (int i{}; i < m_MAXKeyboardAsciiSize; i++)
	{
		if (keyboardCommands[i].command == nullptr) continue;
		if (keyboardCommands[i].isPressed)
		{
			keyboardCommands[i].command->Execute(deltatime);
		}
	}


	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case ControllerButton::DpadL:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::DpadR:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::DpadU:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::DpadD:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	default: return false;
	}
}

void dae::InputManager::ChangeCommand(ControllerButton button, int controller, Command * newcommand)
{
	switch (button)
	{
	case dae::ControllerButton::ButtonA:
		aBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::ButtonB:
		bBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::ButtonX:
		xBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::ButtonY:
		yBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::DpadL:
		padlBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::DpadR:
		padrBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::DpadU:
		paduBtnCommand[controller] = newcommand;
		break;
	case dae::ControllerButton::DpadD:
		paddBtnCommand[controller] = newcommand;
		break;
	default:
		break;
	}
}

void dae::InputManager::ChangeKeyboardCommand(char character, Command * newCommand)
{
	if (int(character) > m_MAXKeyboardAsciiSize) return;

	keyboardCommands[int(character)].command = newCommand;
}


