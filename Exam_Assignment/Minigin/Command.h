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
		virtual ~Command();
		virtual void Execute(float deltatime);
	};

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
}