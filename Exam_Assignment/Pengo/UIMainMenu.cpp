#include "pch.h"
#include "UIMainMenu.h"

dae::UIMainMenu::UIMainMenu(GameObject * parent) 
	: BaseComponent(parent)
{
}

void dae::UIMainMenu::Update(const float & deltaTime)
{
}

void dae::UIMainMenu::Render() const
{
}

void dae::UIMainMenu::StartSolo()
{
	InputManager::GetInstance().ChangeCommand(ControllerButton::ButtonB, 0, nullptr);
	InputManager::GetInstance().ChangeCommand(ControllerButton::ButtonY, 0, nullptr);
	Messenger::GetInstance().Notify(EVENT_STARTSINGLEPLAYER,0);
}

void dae::UIMainMenu::StartCoOp()
{
	InputManager::GetInstance().ChangeCommand(ControllerButton::ButtonB, 0, nullptr);
	InputManager::GetInstance().ChangeCommand(ControllerButton::ButtonY, 0, nullptr);
	Messenger::GetInstance().Notify(EVENT_STARTCOOP,0);
}

void dae::UIMainMenu::StartVS()
{
	InputManager::GetInstance().ChangeCommand(ControllerButton::ButtonB, 0, nullptr);
	InputManager::GetInstance().ChangeCommand(ControllerButton::ButtonY, 0, nullptr);
	Messenger::GetInstance().Notify(EVENT_STARTVS,0);
}

void dae::UIMainMenu::Quit()
{
	Messenger::GetInstance().Notify(EVENT_ENDGAME,0);
}
