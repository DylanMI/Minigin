#include "pch.h"
#include "GameFieldGridComponent.h"

dae::GameFieldGridComponent::GameFieldGridComponent(GameObject * parent, dae::Rectf dimension, int PPW, int PPH, Scene& sceneref)
	: BaseComponent(parent)
	, m_dimension(dimension)
    , m_ammPointsPerWidth(PPW)
	, m_ammPointsPerHeight(PPH)
	, m_SceneRef(sceneref)
{
	m_GridInfo.resize(PPW * PPH, GridInfo());

	// make the coordinates
	int counter{};
	m_distanceBtwPoints = Point2f
	{
		(m_dimension.w / m_ammPointsPerWidth) / 2
		,(m_dimension.h / m_ammPointsPerHeight) / 2
	};
	for (int k{}, s2 = m_ammPointsPerHeight; k < s2; k++)
	{
		for (int i{}, s = m_ammPointsPerWidth; i < s; i++)
		{
			// Width and Height
			float width = m_dimension.x + ((i) * (m_dimension.w / m_ammPointsPerWidth) - (m_distanceBtwPoints.x));
			float height= m_dimension.y + ((k) * (m_dimension.h / m_ammPointsPerHeight) - (m_distanceBtwPoints.y));

			m_GridInfo[counter].coordinate = Point2f{ width, height };
			counter++;
		}
		
	}
}

dae::GameFieldGridComponent::~GameFieldGridComponent()
{
}

void dae::GameFieldGridComponent::Update(const float & deltaTime)
{
}

void dae::GameFieldGridComponent::Render() const
{
}

void dae::GameFieldGridComponent::RemoveData(GameObject * object)
{
	for (int i{}; i < m_GridInfo.size(); i++)
	{
		// recheck entire board, that no false data is left behind
		//if (m_GridInfo[i].object == nullptr)
		//{
		//	m_GridInfo[i].isDiamondBlock = false;
		//	m_GridInfo[i].isObstacle = false;
		//	m_GridInfo[i].isSnoBee = false;
		//	m_GridInfo[i].isEggBlock = false;
		//}
		//else if (object->GetTransform().GetPosition() == m_GridInfo[i].object->GetTransform().GetPosition())
		if (object == m_GridInfo[i].object)
		{
			m_GridInfo[i].object = nullptr;
			m_GridInfo[i].isDiamondBlock = false;
			m_GridInfo[i].isObstacle = false;
			m_GridInfo[i].isSnoBee = false;
			m_GridInfo[i].isEggBlock = false;
		}
	}
}

void dae::GameFieldGridComponent::addEggBlock(GameObject * eggBlock)
{
	m_eggBlocks.push_back(eggBlock);
}

void dae::GameFieldGridComponent::ShowEggBlocks()
{
	for (int i{}; i < m_eggBlocks.size(); i++)
	{
		m_eggBlocks[i]->GetComponent<EggBlockComponent>()->Show(2.0f);
	}
}

int dae::GameFieldGridComponent::GetAmmEggsLeft()
{
	return m_eggBlocks.size();
}

void dae::GameFieldGridComponent::HatchNextEgg()
{
	int currIdx = getCurrGridIndex(Rectf{ m_eggBlocks[0]->GetTransform().GetPosition().x, m_eggBlocks[0]->GetTransform().GetPosition().y, m_eggBlocks[0]->GetComponent<IceBlockComponent>()->getWidthnHeight().x, m_eggBlocks[0]->GetComponent<IceBlockComponent>()->getWidthnHeight().y });

	m_eggBlocks[0]->GetComponent<EggBlockComponent>()->Hatch(currIdx);
	m_eggBlocks[0]->GetComponent<DeleteSelfComponent>()->KillNow();
	
	m_eggBlocks.erase(std::remove(m_eggBlocks.begin(), m_eggBlocks.end(), m_eggBlocks[0]), m_eggBlocks.end());

	m_GridInfo[currIdx].object = nullptr;
	m_GridInfo[currIdx].isEggBlock = false;
	m_GridInfo[currIdx].isObstacle = false;
}

std::vector<dae::GridInfo>& dae::GameFieldGridComponent::getInfoRef()
{
	return m_GridInfo;
}

dae::Scene & dae::GameFieldGridComponent::getSceneRef()
{
	return m_SceneRef;
}

const int dae::GameFieldGridComponent::getCurrGridIndex(dae::Rectf dimensions)
{
	Point2f center = Point2f{ dimensions.x + (dimensions.w / 2),dimensions.y + (dimensions.h / 2) };
	for (int i{}, s = int(m_GridInfo.size()); i < s; i++)
	{
		if (IsPointInSquare(m_GridInfo[i].coordinate, dimensions)) return i;
	}
	return -1; 
}

const int dae::GameFieldGridComponent::getAmmPointPerWidth()
{
	return m_ammPointsPerWidth;
}

const int dae::GameFieldGridComponent::getAmmPointPerHeight()
{
	return m_ammPointsPerHeight;
}
