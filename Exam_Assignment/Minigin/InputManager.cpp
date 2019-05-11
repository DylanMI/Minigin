#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


dae::InputManager::~InputManager()
{
}


bool dae::InputManager::ProcessInput(float deltatime)
{
	for (int i{}; i < m_MAXammControllers; i++)
	{
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		XInputGetState(0, &currentState);
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				return false;
			}
			if (e.type == SDL_KEYDOWN)
			{

			}
			if (e.type == SDL_MOUSEBUTTONDOWN)
			{

			}
		}
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


