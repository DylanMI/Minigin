#include "pch.h"
#include "IceBlockComponent.h"

dae::IceBlockComponent::IceBlockComponent(GameObject * parent, GameFieldGridComponent * gameGridObj)
	:BaseComponent(parent)
	,mp_gameGridObj(gameGridObj)
	,m_glidingDirection(direction::NONE)
	,m_isGliding(false)
{
}

dae::IceBlockComponent::~IceBlockComponent()
{
}

void dae::IceBlockComponent::Update(const float & deltaTime)
{
	if (m_isGliding)
	{
		switch (m_glidingDirection)
		{
		case direction::LEFT:
			// check if you can go that way without getting of the grid
			
			// check if there is already a block
			// if there is then break

			break;

		case direction::RIGHT:
			// check if you can go that way without getting of the grid

			// check if there is already a block
			// if there is then break

			break;


		case direction::UP:
			// check if you can go that way without getting of the grid

			// check if there is already a block
			// if there is then break
			
			break;

		case direction::DOWN:
			// check if you can go that way without getting of the grid

			// check if there is already a block
			// if there is then break
			
			break;

		default:
			throw;
			break;
		}
	}

}

void dae::IceBlockComponent::Render() const
{
}

void dae::IceBlockComponent::SetIsGliding(bool newbool)
{
	m_isGliding = newbool;
}

void dae::IceBlockComponent::SetGlidingDirection(direction newDirection)
{
	m_glidingDirection = newDirection;
}
