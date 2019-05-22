#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

#include "CollisionComponent.h"
#include "CollisionManager.h"

namespace dae
{
	class GameObject;
	class DeleteSelfComponent : public BaseComponent
	{
	public:
		explicit DeleteSelfComponent(GameObject* parent, Scene& scene);
		virtual ~DeleteSelfComponent() = default;
		DeleteSelfComponent(const DeleteSelfComponent& other) = delete;
		DeleteSelfComponent(DeleteSelfComponent&& other) = delete;
		DeleteSelfComponent& operator=(const DeleteSelfComponent& other) = delete;
		DeleteSelfComponent& operator=(DeleteSelfComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		void StartSelfDestruct(float time);
		void KillNow();
	private:

		void HandleEvent();

		GameObject* m_pParent;
		Scene& m_scene;

		bool m_isTicking;
		float m_deleteTimer;
	};

}

