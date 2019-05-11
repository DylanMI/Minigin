#pragma once
#include "GameObject.h"
#include "ServiceLocator.h"

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
/*
	class MoveLeftCommand : public Command
	{
	public:
		MoveLeftCommand(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveRightCommand : public Command
	{
	public:
		MoveRightCommand(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveUpCommand : public Command
	{
	public:
		MoveUpCommand(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class MoveDownCommand : public Command
	{
	public:
		MoveDownCommand(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

	class FireCommand : public Command
	{
	public:
		FireCommand(GameObject* object);
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};*/
}
