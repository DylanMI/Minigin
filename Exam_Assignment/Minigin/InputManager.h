#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		DpadL,
		DpadR,
		DpadU,
		DpadD
	};

	enum class Controller
	{
		One,
		Two,
		Three,
		Four
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		~InputManager();
		bool ProcessInput(float deltatime);
		bool IsPressed(ControllerButton button) const;
		void ChangeCommand(ControllerButton button,int controller, Command* newcommand);
	private:
		XINPUT_STATE currentState{};
		static const int m_MAXammControllers = 4;
		// command states
		Command* aBtnCommand[m_MAXammControllers];
		Command* bBtnCommand[m_MAXammControllers];
		Command* xBtnCommand[m_MAXammControllers];
		Command* yBtnCommand[m_MAXammControllers];
		Command* padlBtnCommand[m_MAXammControllers];
		Command* padrBtnCommand[m_MAXammControllers];
		Command* paduBtnCommand[m_MAXammControllers];
		Command* paddBtnCommand[m_MAXammControllers];	
	};
}