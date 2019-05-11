#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


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
			switch (i)
			{
			case 0:
				if (aBtnCommand_One != nullptr) aBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (aBtnCommand_Two != nullptr) aBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (aBtnCommand_Three != nullptr) aBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (aBtnCommand_Four != nullptr) aBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}	
		}
		if (IsPressed(ControllerButton::ButtonB))
		{
			switch (i)
			{
			case 0:
				if (bBtnCommand_One != nullptr) bBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (bBtnCommand_Two != nullptr) bBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (bBtnCommand_Three != nullptr) bBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (bBtnCommand_Four != nullptr) bBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}			
		}
		if (IsPressed(ControllerButton::ButtonX))
		{
			switch (i)
			{
			case 0:
				if (xBtnCommand_One != nullptr) xBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (xBtnCommand_Two != nullptr) xBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (xBtnCommand_Three != nullptr) xBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (xBtnCommand_Four != nullptr) xBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}
		}
		if (IsPressed(ControllerButton::ButtonY))
		{
			switch (i)
			{
			case 0:
				if (yBtnCommand_One != nullptr) yBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (yBtnCommand_Two != nullptr) yBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (yBtnCommand_Three != nullptr) yBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (yBtnCommand_Four != nullptr) yBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}
		}
		if (IsPressed(ControllerButton::DpadL))
		{
			switch (i)
			{
			case 0:
				if (padlBtnCommand_One != nullptr) padlBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (padlBtnCommand_Two != nullptr) padlBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (padlBtnCommand_Three != nullptr) padlBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (padlBtnCommand_Four != nullptr) padlBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}
		}
		if (IsPressed(ControllerButton::DpadR))
		{
			switch (i)
			{
			case 0:
				if (padrBtnCommand_One != nullptr) padrBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (padrBtnCommand_Two != nullptr) padrBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (padrBtnCommand_Three != nullptr) padrBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (padrBtnCommand_Four != nullptr) padrBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}
		}
		if (IsPressed(ControllerButton::DpadU))
		{
			switch (i)
			{
			case 0:
				if (paduBtnCommand_One != nullptr) paduBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (paduBtnCommand_Two != nullptr) paduBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (paduBtnCommand_Three != nullptr) paduBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (paduBtnCommand_Four != nullptr) paduBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}
		}
		if (IsPressed(ControllerButton::DpadD))
		{
			switch (i)
			{
			case 0:
				if (paddBtnCommand_One != nullptr) paddBtnCommand_One->Execute(deltatime);
				break;
			case 1:
				if (paddBtnCommand_Two != nullptr) paddBtnCommand_Two->Execute(deltatime);
				break;
			case 2:
				if (paddBtnCommand_Three != nullptr) paddBtnCommand_Three->Execute(deltatime);
				break;
			case 3:
				if (paddBtnCommand_Four != nullptr) paddBtnCommand_Four->Execute(deltatime);
				break;
			default:
				return false;
				break;
			}
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
		if (controller == 0) aBtnCommand_One = newcommand;
			if (controller == 1) aBtnCommand_Two = newcommand;
				if (controller == 2) aBtnCommand_Three = newcommand;
					if(controller == 3) aBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::ButtonB:
		if (controller == 0) bBtnCommand_One = newcommand;
			if (controller == 1) bBtnCommand_Two = newcommand;
				if (controller == 2) bBtnCommand_Three = newcommand;
					if(controller == 3) bBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::ButtonX:
		if (controller == 0) xBtnCommand_One = newcommand;
			if (controller == 1) xBtnCommand_Two = newcommand;
				if (controller == 2) xBtnCommand_Three = newcommand;
					if(controller == 3) xBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::ButtonY:
		if (controller == 0) yBtnCommand_One = newcommand;
			if (controller == 1) yBtnCommand_Two = newcommand;
				if (controller == 2) yBtnCommand_Three = newcommand;
					if(controller == 3) yBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::DpadL:
		if (controller == 0) padlBtnCommand_One = newcommand;
			if (controller == 1) padlBtnCommand_Two = newcommand;
				if (controller == 2) padlBtnCommand_Three = newcommand;
					if(controller == 3) padlBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::DpadR:
		if (controller == 0) padrBtnCommand_One = newcommand;
			if (controller == 1) padrBtnCommand_Two = newcommand;
				if (controller == 2) padrBtnCommand_Three = newcommand;
					if(controller == 3) padrBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::DpadU:
		if (controller == 0) paduBtnCommand_One = newcommand;
			if (controller == 1) paduBtnCommand_Two = newcommand;
				if (controller == 2) paduBtnCommand_Three = newcommand;
					if(controller == 3) paduBtnCommand_Four = newcommand;
		break;
	case dae::ControllerButton::DpadD:
		if (controller == 0) paddBtnCommand_One = newcommand;
			if (controller == 1) paddBtnCommand_Two = newcommand;
				if (controller == 2) paddBtnCommand_Three = newcommand;
					if(controller == 3) paddBtnCommand_Four = newcommand;
		break;
	default:
		break;
	}
}


