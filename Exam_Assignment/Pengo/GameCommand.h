#pragma once
#include <Command.h>

class ServiceLocator;
class GameObject;
namespace dae
{
	class GameCommand : public Command
	{
	public:
		virtual ~GameCommand() override;
		virtual void Execute(float deltatime) override;
	};

	class GameCollisionCommand : public CollisionCommand
	{
	public:
		virtual ~GameCollisionCommand() override;
		virtual void Execute(float deltatime, GameObject* self, GameObject* other) override;
	};

#pragma region playerMovement

	class MoveLeftCommandPlayer : public Command
	{
	public:
		MoveLeftCommandPlayer(GameObject* object);
		virtual ~MoveLeftCommandPlayer() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveRightCommandPlayer : public Command
	{
	public:
		MoveRightCommandPlayer(GameObject* object);
		virtual ~MoveRightCommandPlayer() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveUpCommandPlayer : public Command
	{
	public:
		MoveUpCommandPlayer(GameObject* object);
		virtual ~MoveUpCommandPlayer() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveDownCommandPlayer : public Command
	{
	public:
		MoveDownCommandPlayer(GameObject* object);
		virtual ~MoveDownCommandPlayer() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

#pragma endregion

#pragma region PlayerInteractions

	class InteractCommand : public Command
	{
	public:
		InteractCommand(GameObject* object);
		virtual ~InteractCommand() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

#pragma endregion

#pragma region MainMenu
	class StartSoloCommand : public Command
	{
	public:
		StartSoloCommand(GameObject* object);
		virtual ~StartSoloCommand() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class StartCOOPCommand : public Command
	{
	public:
		StartCOOPCommand(GameObject* object);
		virtual ~StartCOOPCommand() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class StartVSCommand : public Command
	{
	public:
		StartVSCommand(GameObject* object);
		virtual ~StartVSCommand() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};


	class QuitCommand : public Command
	{
	public:
		QuitCommand(GameObject* object);
		virtual ~QuitCommand() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};
#pragma endregion

} 