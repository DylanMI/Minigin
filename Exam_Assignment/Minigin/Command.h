#pragma once
#include "GameObject.h"
#include "ServiceLocator.h"
#include "PlayerCharacter.h"


class ServiceLocator;
class GameObject;
namespace dae
{
	class Command
	{
	public:
		~Command() = default;
		virtual void Execute(float deltatime);
	};

	class MoveLeftCommandPlayer : public Command
	{
	public:
		MoveLeftCommandPlayer(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveRightCommandPlayer : public Command
	{
	public:
		MoveRightCommandPlayer(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveUpCommandPlayer : public Command
	{
	public:
		MoveUpCommandPlayer(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveDownCommandPlayer : public Command
	{
	public:
		MoveDownCommandPlayer(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};
}