#pragma once
#include "GameObject.h"
#include "ServiceLocator.h"

#include "RockComponent.h"
#include "PookaComponent.h"
#include "FygarComponent.h"
#include "GunComponent.h"
#include "DeleteSelfComponent.h"

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


	class CollisionCommand
	{
	public:
		virtual ~CollisionCommand();
		virtual void Execute(float deltatime, GameObject* self ,GameObject* other);
	};

#pragma region movementcommands
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

	class ShootCommandPlayer : public Command
	{
	public:
		ShootCommandPlayer(GameObject* object);
		virtual ~ShootCommandPlayer() override;
		void Execute(float deltatime) override;
	private:
		GameObject* m_object;
	};

#pragma endregion

#pragma region RockCommands
	class FallCommandRock : public CollisionCommand
	{
	public:
		FallCommandRock(GameObject* object);
		virtual ~FallCommandRock() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

	class BreakCommandRock : public CollisionCommand
	{
	public:
		BreakCommandRock(GameObject* object);
		virtual ~BreakCommandRock() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

	class TakeEnemyCommandRock : public CollisionCommand
	{
	public:
		TakeEnemyCommandRock(GameObject* object);
		virtual ~TakeEnemyCommandRock() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

#pragma endregion

#pragma region EnemyCommands
	class RandomizeDirectionCommandEnemy : public CollisionCommand
	{
	public:
		RandomizeDirectionCommandEnemy(GameObject* object);
		virtual ~RandomizeDirectionCommandEnemy() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;

	private:
		GameObject* m_object;
	};

	class HitByBlowerPooka : public CollisionCommand
	{
	public:
		HitByBlowerPooka(GameObject* object);
		virtual ~HitByBlowerPooka() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

	class HitByBlowerFygar : public CollisionCommand
	{
	public:
		HitByBlowerFygar(GameObject* object);
		virtual ~HitByBlowerFygar() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

	class HitByRock : public CollisionCommand
	{
	public:
		HitByRock(GameObject* object);
		virtual ~HitByRock() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;

	};

	class PlayerHitEnemy : public CollisionCommand
	{
	public:
		PlayerHitEnemy(GameObject* object);
		virtual ~PlayerHitEnemy() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

	class PlayerHitRock : public CollisionCommand
	{
	public:
		PlayerHitRock(GameObject* object);
		virtual ~PlayerHitRock() override;
		void Execute(float deltatime, GameObject* self, GameObject* other) override;
	private:
		GameObject* m_object;
	};

#pragma endregion

}