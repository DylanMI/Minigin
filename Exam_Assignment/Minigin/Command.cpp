#include "MiniginPCH.h"
#include "Command.h"
#include "CollisionCheckerComponent.h"


dae::Command::~Command()
{
}

void dae::Command::Execute(float /*deltatime*/)
{}

dae::CollisionCommand::~CollisionCommand()
{
}

void dae::CollisionCommand::Execute(float /*deltatime*/, GameObject* /*self*/, GameObject * /*other*/)
{}

#pragma region movementcommands
dae::MoveLeftCommandPlayer::MoveLeftCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveLeftCommandPlayer::~MoveLeftCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveLeftCommandPlayer::Execute(float deltatime)
{
	m_object->Move(Point2f{ -1,0 }, deltatime);
}

dae::MoveRightCommandPlayer::MoveRightCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveRightCommandPlayer::~MoveRightCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveRightCommandPlayer::Execute(float deltatime)
{
	m_object->Move(Point2f{ 1,0 }, deltatime);
}

dae::MoveUpCommandPlayer::MoveUpCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveUpCommandPlayer::~MoveUpCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveUpCommandPlayer::Execute(float deltatime)
{
	m_object->Move(Point2f{ 0,1 }, deltatime);
}

dae::MoveDownCommandPlayer::MoveDownCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::MoveDownCommandPlayer::~MoveDownCommandPlayer()
{
	//delete m_object;
	m_object = nullptr;
}

void dae::MoveDownCommandPlayer::Execute(float deltatime)
{
	m_object->Move(Point2f{ 0,-1 }, deltatime);
}


dae::ShootCommandPlayer::ShootCommandPlayer(GameObject * object)
	:m_object(object)
{}

dae::ShootCommandPlayer::~ShootCommandPlayer()
{
	m_object = nullptr;
}

void dae::ShootCommandPlayer::Execute(float)
{
	if (m_object->GetComponent<GunComponent>()->GetCanShoot())
	{
		m_object->GetComponent<GunComponent>()->Shoot();
	}
}


#pragma endregion

#pragma region RockCommands

dae::FallCommandRock::FallCommandRock(GameObject * object)
	:m_object(object)
{}

dae::FallCommandRock::~FallCommandRock()
{
	m_object = nullptr;
}

// executed when the collision doesn't collide with anyting
void dae::FallCommandRock::Execute(float, GameObject* , GameObject* /*other*/)
{
	// check if the rock is already falling, if not make it falling
	if (!m_object->GetComponent<RockComponent>()->GetIsFalling())
	{
		m_object->GetComponent<RockComponent>()->SetIsFalling(true);

		// also change the body to fit the rock itself (AKA: no offset)
		m_object->GetComponent<CollisionCheckerComponent>()->SetOffset({ 0,0 });
		m_object->GetComponent<CollisionCheckerComponent>()->SetWidthAndHeightBody({ 16,16 });

	}
}

dae::BreakCommandRock::BreakCommandRock(GameObject * object)
	:m_object(object)
{}

dae::BreakCommandRock::~BreakCommandRock()
{
	m_object = nullptr;
}

// exectuted after the collision detects terrain and is falling
void dae::BreakCommandRock::Execute(float, GameObject* , GameObject* /*other*/)
{
	// check if the rock is falling, if yes then set it to breaking
	if (m_object->GetComponent<RockComponent>()->GetIsFalling())
	{
		m_object->GetComponent<RockComponent>()->SetIsBreaking(true);
	}
}

dae::TakeEnemyCommandRock::TakeEnemyCommandRock(GameObject * object)
	:m_object(object)
{}

dae::TakeEnemyCommandRock::~TakeEnemyCommandRock()
{
	m_object = nullptr;
}

// exectuted when the collision detects an enemy and is falling
void dae::TakeEnemyCommandRock::Execute(float, GameObject* , GameObject* )
{
	// add Enemy to the rock if the rock isfalling is true
}

#pragma endregion

#pragma region EnemyCommands
dae::RandomizeDirectionCommandEnemy::RandomizeDirectionCommandEnemy(GameObject * object)
	:m_object(object)
{}

dae::RandomizeDirectionCommandEnemy::~RandomizeDirectionCommandEnemy()
{
	m_object = nullptr;
}

void dae::RandomizeDirectionCommandEnemy::Execute(float deltatime, GameObject* , GameObject * )
{
	m_object->GetComponent<PookaComponent>()->PutBackAFrame(deltatime);
	m_object->GetComponent<PookaComponent>()->ShiftDirection();
}

dae::HitByBlowerPooka::HitByBlowerPooka(GameObject * object)
	:m_object(object)
{}

dae::HitByBlowerPooka::~HitByBlowerPooka()
{
	m_object = nullptr;
}

void dae::HitByBlowerPooka::Execute(float, GameObject* , GameObject *other)
{
	m_object->GetComponent<PookaComponent>()->AddblowCount(1);
	m_object->GetComponent<PookaComponent>()->SetIsInflated(true);
	other->GetComponent<DeleteSelfComponent>()->KillNow();
}


dae::HitByRock::HitByRock(GameObject* object)
	:m_object(object)
{}

dae::HitByRock::~HitByRock()
{
	m_object = nullptr;
}

void dae::HitByRock::Execute(float, GameObject* self, GameObject * other)
{
	// check if the rock is falling
	if (other->GetComponent<RockComponent>()->GetIsFalling())
	{
		// if it is, then add yourself to its victim vector, and set state to falling, whilst falling it will follow the rock object it has downwards
		// once the rock breaks, the rock will call the death function to handle the points and to kill the enemy
		
		// also check if the victim is already there
		if (!other->GetComponent<RockComponent>()->IsVictimAlreadyRegistered(self))
		{
			other->GetComponent<RockComponent>()->AddVictim(self);
			// then also set the state of self, towards CAUGHTBYROCK
			
			// check if its a pooka
			if (self->GetComponent<PookaComponent>())
			{
				self->GetComponent<PookaComponent>()->SetState(State::CAUGHTBYROCK);
			}

			// check if its a fygar

			// cehck if its a player


		}
		
	}
}


dae::PlayerHitPooka::PlayerHitPooka(GameObject* object)
	:m_object(object)
{}


dae::PlayerHitPooka::~PlayerHitPooka()
{
}

void dae::PlayerHitPooka::Execute(float , GameObject *self, GameObject * )
{
	// put the player back to a position
	self->SetPosition(Point2f{ 0,0 });

	// tell the messenger about it
	Messenger::instance().Notify(Event::EVENT_DIED);
}


#pragma endregion
