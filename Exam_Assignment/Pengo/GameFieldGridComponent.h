#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	struct GridInfo
	{
		GameObject* object;
		Point2f coordinate;
		bool isObstacle;
		bool isDiamondBlock;
		bool isSnoBee;
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

		// will be calculated
		Point2f m_distanceBtwPoints;
		std::vector<GridInfo> m_GridInfo;
		Scene& m_SceneRef;
	
	};

}
