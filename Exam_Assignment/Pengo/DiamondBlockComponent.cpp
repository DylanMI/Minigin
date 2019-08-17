#include "pch.h"
#include "DiamondBlockComponent.h"

dae::DiamondBlockComponent::DiamondBlockComponent(GameObject * parent, GameObject * gameGridObj)
	: BaseComponent(parent)
	, mp_gameGridObj(gameGridObj)
{
}

dae::DiamondBlockComponent::~DiamondBlockComponent()
{
}

void dae::DiamondBlockComponent::Update(const float & deltaTime)
{
	// check if you are next to other diamond blocks
	// get the current position
	
	Point2f currPos = m_pParent->GetComponent<IceBlockComponent>()->getCurrPos();
	Point2f WnH = m_pParent->GetComponent<IceBlockComponent>()->getWidthnHeight();

	int currIdx = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getCurrGridIndex(Rectf{ currPos.x, currPos.y, WnH.x, WnH.y });

	int ammPointsW = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerWidth();
	int ammPointsH = mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getAmmPointPerHeight();

	// horizontal
	// check if you are at a horizontal border, or out of bounds with your next check
	if (currIdx % ammPointsW == 0 || currIdx % ammPointsW == ammPointsW - 1)
	{
		// do nothing
	}
	// check if its actually there
	else if
		(
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - 1].isDiamondBlock
			&& mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + 1].isDiamondBlock
		)
	{
		// Fire DiamondChain Event

		return;
	}
	// vertical
	// check if you are at a vertical border, or out of bounds with your next check
	if (currIdx - ammPointsW < 0 || currIdx + ammPointsW >= mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef().size())
	{
		// do nothing
	}
	// check if its actually there
	else if
		(
			mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx - ammPointsW].isDiamondBlock
			&& mp_gameGridObj->GetComponent<GameFieldGridComponent>()->getInfoRef()[currIdx + ammPointsW].isDiamondBlock
		)
	{
		// Fire DiamondChain Event
			
		return;
	}

}

void dae::DiamondBlockComponent::Render() const
{
}
