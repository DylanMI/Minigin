#include "pch.h"
#include "IceBlockComponent.h"

dae::IceBlockComponent::IceBlockComponent(GameObject * parent,Point2f WidthAndHeight,GameObject * gameGridObj)
	:BaseComponent(parent)
	,mp_gameGridObj(gameGridObj)
	,m_glidingDirection(direction::NONE)
	,m_isGliding(false)
	, m_WidthAndHeight(WidthAndHeight)
{
}


dae::IceBlockComponent::~IceBlockComponent()
{
}

void dae::IceBlockComponent::Update(const float & deltaTime)
{
	m_pParent->SetPosition(m_currPos);

	// should be gliding but is not travelling (arrived at grid, or arrived at wall etc...)
	if (m_isGliding && m_isTraveling == false)
	{
		int IdxLeft{};
		int IdxRight{};
		int IdxAbove{};
		int IdxBelow{};

		// get the current position
		int currIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });

		int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
		int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

		switch (m_glidingDirection)
		{
		case direction::LEFT:
			// check if you can go that way without getting of the grid
			// check if you are at the left border
			if (currIdx == 0)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			if (currIdx % ammPointsW == 0)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
			}
			// check if there is already a block
			IdxLeft = currIdx - 1;
			GridInfo infoLeft = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxLeft];
			if (infoLeft.isObstacle)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			break;

		case direction::RIGHT:
			// check if you can go that way without getting of the grid
			if (currIdx == 0)
			{
				m_start = m_currPos;
				m_destination = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[currIdx + 1].coordinate;
				m_isGliding = true;
				m_isTraveling = true;
				return;
			}

			// check if you are at the right border
			if (currIdx % ammPointsW == ammPointsW - 1)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
			}

			// check if there is already a block
			IdxRight = currIdx + 1;
			GridInfo infoRight = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxRight];
			if (infoRight.isObstacle)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			break;


		case direction::UP:
			// check if you can go that way without getting of the grid
			if (currIdx - ammPointsW < 0)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			// check if there is already a block
			IdxAbove = currIdx - ammPointsW;
			GridInfo infoAbove = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxAbove];
			if (infoAbove.isObstacle)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			
			break;

		case direction::DOWN:
			// check if you can go that way without getting of the grid
			if (currIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo().size())
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			// check if there is already a block
			IdxBelow = currIdx + ammPointsW;
			GridInfo infoBelow = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxBelow];
			if (infoBelow.isObstacle)
			{
				m_isGliding = false;
				m_isTraveling = false;
				m_destination = m_currPos;
				return;
			}
			
			break;

		default:
			throw;
			break;
		}
	}
	// if it is travelling, lerp to the pos
	else if (m_isTraveling == true)
	{

		LerpPos(deltaTime);

	
	}

}

void dae::IceBlockComponent::Render() const
{
}

void dae::IceBlockComponent::SetPosition(int idxPos)
{
	m_currPos = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[idxPos].coordinate;
}

void dae::IceBlockComponent::StartGliding(direction glidingDirection)
{
	int IdxLeft{};
	int IdxRight{};
	int IdxAbove{};
	int IdxBelow{};

	// check if the direction you are gliding to is blocked
	// get the current position
	int currIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ m_currPos.x, m_currPos.y, m_WidthAndHeight.x, m_WidthAndHeight.y });

	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();
	
	switch (glidingDirection)
	{
	case direction::LEFT:
		if (currIdx == 0 || currIdx % ammPointsW == 0) return;
		IdxLeft = currIdx - 1;
		GridInfo infoLeft = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxLeft];
		if (infoLeft.isObstacle) return;
		break;
	case direction::RIGHT:
		if (currIdx == 0 || currIdx % ammPointsW == ammPointsW - 1) return;
		IdxRight = currIdx + 1;
		GridInfo infoRight = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxRight];
		if (infoRight.isObstacle) return;
		break;
	case direction::UP:
		if (currIdx - ammPointsW < 0) return;
		IdxAbove = currIdx - ammPointsW;
		GridInfo infoAbove = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxAbove];
		if (infoAbove.isObstacle) return;
		break;
	case direction::DOWN:
		if (currIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo().size()) return;
		IdxBelow = currIdx + ammPointsW;
		GridInfo infoBelow = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfo()[IdxBelow];
		if (infoBelow.isObstacle) return;
		break;

	default:
		throw;
		break;
	}

	m_isGliding = true;
	m_glidingDirection = glidingDirection;
}

void dae::IceBlockComponent::StopGliding()
{
	m_isGliding = false;
	m_glidingDirection = direction::NONE;
}


dae::Point2f dae::IceBlockComponent::LerpPos(float DT)
{
	T += DT * m_Speed;
	if (T > 1)
	{
		T = 1;
		m_currPos = lerp(m_start, m_destination, T);
		T = 0;
		m_isTraveling = false;
		return m_currPos;
	}
	else
	{
		m_currPos = lerp(m_start, m_destination, T);
		return m_currPos;
	}
}