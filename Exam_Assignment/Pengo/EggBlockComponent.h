#pragma once
#include <BaseComponent.h>

namespace dae
{
	class EggBlockComponent : public BaseComponent
	{
	public:
		explicit EggBlockComponent(GameObject* parent, GameObject * gameGridObj, Scene& sceneRef);
		virtual ~EggBlockComponent();
		EggBlockComponent(const EggBlockComponent& other) = delete;
		EggBlockComponent(EggBlockComponent&& other) = delete;
		EggBlockComponent& operator=(const EggBlockComponent& other) = delete;
		EggBlockComponent& operator=(EggBlockComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
	
		void Hatch(int positionIdx);
		void Show(float time);

	private:
		GameObject * mp_gameGridObj;
		Scene& m_SceneRef;


		// show variables
		float m_timer;
		float m_showTime;
		
		bool m_isShowing;
	
	};


}

