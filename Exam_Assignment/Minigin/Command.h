#pragma once
#include "GameObject.h"
#include "ServiceLocator.h"

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


}