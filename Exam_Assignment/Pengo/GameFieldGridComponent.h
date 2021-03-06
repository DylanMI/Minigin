#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "PlayerPengoMovementComponent.h"

namespace dae
{
	struct GridInfo
	{
		GameObject* object;
		Point2f coordinate;
		bool isObstacle;
		bool isDiamondBlock;
		bool isSnoBee;
		bool isEggBlock;
	};

	class GameFieldGridComponent : public BaseComponent
	{
	public:
		explicit GameFieldGridComponent(GameObject* parent, dae::Rectf dimension, int PPW, int PPH, Scene& sceneref);
		virtual ~GameFieldGridComponent();
		GameFieldGridComponent(const GameFieldGridComponent& other) = delete;
		GameFieldGridComponent(GameFieldGridComponent&& other) = delete;
		GameFieldGridComponent& operator=(const GameFieldGridComponent& other) = delete;
		GameFieldGridComponent& operator=(GameFieldGridComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	
		void RemoveData(GameObject* object);

		void addEggBlock(GameObject* eggBlock);
		void ShowEggBlocks();
		int GetAmmEggsLeft();
		void HatchNextEgg();
		void RemoveEgg(GameObject* eggInQuestion);

		void MakeBoundryWalls();
		void ActivateWall(direction direct);
		
		std::vector<GridInfo>& getInfoRef();
		Scene& getSceneRef();
		const int getCurrGridIndex(dae::Rectf dimensions);
		const int getAmmPointPerWidth();
		const int getAmmPointPerHeight();
	private:
		
		// will be initialized
		Rectf m_dimension;
		int m_ammPointsPerWidth;
		int m_ammPointsPerHeight;
		Scene& m_SceneRef;

		// will be defined by level loader
		std::vector<GameObject*> m_eggBlocks;

		std::vector<GameObject*> m_walls;

		// will be calculated
		Point2f m_distanceBtwPoints;
		std::vector<GridInfo> m_GridInfo;
		
	
	};

}
