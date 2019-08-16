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
