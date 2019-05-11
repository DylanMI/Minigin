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
		bool ProcessInput(float deltatime);
		bool IsPressed(ControllerButton button) const;
		void ChangeCommand(ControllerButton button,int controller, Command* newcommand);
	private:
		XINPUT_STATE currentState{};
		
		// command states
		Command* aBtnCommand_One, *aBtnCommand_Two, *aBtnCommand_Three, *aBtnCommand_Four;
		Command* bBtnCommand_One, *bBtnCommand_Two, *bBtnCommand_Three, *bBtnCommand_Four;
		Command* xBtnCommand_One, *xBtnCommand_Two, *xBtnCommand_Three, *xBtnCommand_Four;
		Command* yBtnCommand_One, *yBtnCommand_Two, *yBtnCommand_Three, *yBtnCommand_Four;
		Command* padlBtnCommand_One, *padlBtnCommand_Two, *padlBtnCommand_Three, *padlBtnCommand_Four;
		Command* padrBtnCommand_One, *padrBtnCommand_Two, *padrBtnCommand_Three, *padrBtnCommand_Four;
		Command* paduBtnCommand_One, *paduBtnCommand_Two, *paduBtnCommand_Three, *paduBtnCommand_Four;
		Command* paddBtnCommand_One, *paddBtnCommand_Two, *paddBtnCommand_Three, *paddBtnCommand_Four;

		const int m_MAXammControllers = 4;
	};

}


