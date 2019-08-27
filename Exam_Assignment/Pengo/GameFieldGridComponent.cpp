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

	MakeBoundryWalls();
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
	return int(m_eggBlocks.size());
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

void dae::GameFieldGridComponent::RemoveEgg(GameObject * eggInQuestion)
{
	m_eggBlocks.erase(std::remove(m_eggBlocks.begin(), m_eggBlocks.end(), eggInQuestion), m_eggBlocks.end());
}

void dae::GameFieldGridComponent::MakeBoundryWalls()
{
	// up wall
	// -- make object, top left
	GameObject* topWall = new GameObject();
	
	// -- give it the wall component
	topWall->AddComponent(new WallComponent(topWall));

	// put it correctly
	topWall->SetPosition(Point2f{ m_GridInfo[0].coordinate.x - 32, m_GridInfo[0].coordinate.y - 16});

	// -- give it a texture
	topWall->AddComponent(new TextureComponent(topWall));
	topWall->GetComponent<TextureComponent>()->SetTexture("WallBlue.png");
	topWall->GetComponent<TextureComponent>()->SetWidthAndHeight(int(m_GridInfo[m_ammPointsPerWidth - 1].coordinate.x - m_GridInfo[0].coordinate.x + 64), 16);
	topWall->GetComponent<TextureComponent>()->SetIsAnimated(false);
	m_walls.push_back(topWall);

	// down wall
	// -- make object, left bottom
	GameObject* botWall = new GameObject();
	
	// -- give it the wall component
	botWall->AddComponent(new WallComponent(botWall));
	
	// put it correctly
	botWall->SetPosition(Point2f{ m_GridInfo[0].coordinate.x - 32, m_GridInfo[m_ammPointsPerHeight * m_ammPointsPerWidth - 1].coordinate.y + 32 });

	// -- give it a texture
	botWall->AddComponent(new TextureComponent(botWall));
	botWall->GetComponent<TextureComponent>()->SetTexture("WallBlue.png");
	botWall->GetComponent<TextureComponent>()->SetWidthAndHeight(int(m_GridInfo[m_ammPointsPerWidth - 1].coordinate.x - m_GridInfo[0].coordinate.x + 64), 16);
	botWall->GetComponent<TextureComponent>()->SetIsAnimated(false);
	m_walls.push_back(botWall);
	
	// left wall
	// -- make object, left bottom
	GameObject* leftWall = new GameObject();

	// -- give it the wall component
	leftWall->AddComponent(new WallComponent(leftWall));

	// put it correctly
	leftWall->SetPosition(Point2f{ m_GridInfo[0].coordinate.x - 16, m_GridInfo[0].coordinate.y - 16 });

	// -- give it a texture
	leftWall->AddComponent(new TextureComponent(leftWall));
	leftWall->GetComponent<TextureComponent>()->SetTexture("WallBlue.png");
	leftWall->GetComponent<TextureComponent>()->SetWidthAndHeight(16 , int(m_GridInfo[m_ammPointsPerHeight * m_ammPointsPerWidth - 1].coordinate.y - m_GridInfo[0].coordinate.y + 64));
	leftWall->GetComponent<TextureComponent>()->SetIsAnimated(false);
	m_walls.push_back(leftWall);

	// right wall	
	// -- make object, right bottom
	GameObject* rightWall = new GameObject();
	
	// -- give it the wall component
	rightWall->AddComponent(new WallComponent(rightWall));

	// put it correctly
	rightWall->SetPosition(Point2f{ m_GridInfo[m_ammPointsPerWidth - 1].coordinate.x + 32, m_GridInfo[0].coordinate.y - 16 });

	// -- give it a texture
	rightWall->AddComponent(new TextureComponent(rightWall));
	rightWall->GetComponent<TextureComponent>()->SetTexture("WallBlue.png");
	rightWall->GetComponent<TextureComponent>()->SetWidthAndHeight(16, int(m_GridInfo[m_ammPointsPerHeight * m_ammPointsPerWidth - 1].coordinate.y - m_GridInfo[0].coordinate.y + 64));
	rightWall->GetComponent<TextureComponent>()->SetIsAnimated(false);
	m_walls.push_back(rightWall);
	
	for (int i{}; i < m_walls.size(); i++)
	{
		m_SceneRef.Add(m_walls[i]);
	}
}

void dae::GameFieldGridComponent::ActivateWall(direction direct)
{
	switch (direct)
	{
		// 3
	case dae::LEFT:
		m_walls[2]->GetComponent<WallComponent>()->Activate();
		break;
		// 4
	case dae::RIGHT:
		m_walls[3]->GetComponent<WallComponent>()->Activate();
		break;
		//1
	case dae::UP:
		m_walls[0]->GetComponent<WallComponent>()->Activate();
		break;
		//2
	case dae::DOWN:
		m_walls[1]->GetComponent<WallComponent>()->Activate();
		break;
	case dae::NONE:
		throw;
		break;
	default:
		throw;
		break;
	}
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

	// recheck with a slight offset, could be precisely on a border
	center.x += 0.5f;
	center.y += 0.5f;
	for (int i{}, s = int(m_GridInfo.size()); i < s; i++)
	{
		if (IsPointInSquare(m_GridInfo[i].coordinate, dimensions)) return i;
	}

	// if even that fails, return -1 
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
