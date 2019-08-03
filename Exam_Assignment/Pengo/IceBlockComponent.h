#pragma once
#include <BaseComponent.h>
namespace dae
{
	class IceBlockComponent : public BaseComponent
	{
	public:
		explicit IceBlockComponent(GameObject* parent,GameFieldGridComponent * gameGridObj);
		virtual ~IceBlockComponent();
		IceBlockComponent(const IceBlockComponent& other) = delete;
		IceBlockComponent(IceBlockComponent&& other) = delete;
		IceBlockComponent& operator=(const IceBlockComponent& other) = delete;
		IceBlockComponent& operator=(IceBlockComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;

		void SetIsGliding(bool newbool);
		void SetGlidingDirection(direction newDirection);

	private:
		direction m_glidingDirection;
		bool m_isGliding;
		GameFieldGridComponent * mp_gameGridObj;
	};

}

