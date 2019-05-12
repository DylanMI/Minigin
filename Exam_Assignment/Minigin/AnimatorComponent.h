#pragma once
#include "GameObject.h"
#include "BaseComponent.h"
#include "BaseCharacter.h"
#include <map>
#include "Texture2D.h"
#include "TextureComponent.h"

class BaseComponent;
class GameObject;
class Texture2D;


namespace dae
{
	class AnimatorComponent : public BaseComponent
	{
	public:
		explicit AnimatorComponent(GameObject* parent);
		virtual ~AnimatorComponent() = default;
		AnimatorComponent(const AnimatorComponent& other) = delete;
		AnimatorComponent(AnimatorComponent&& other) = delete;
		AnimatorComponent& operator=(const AnimatorComponent& other) = delete;
		AnimatorComponent& operator=(AnimatorComponent&& other) = delete;

		void Update(const float& deltaTime) override;
		void Render() const override;
		void AddAnimation(State CharacterState, std::shared_ptr<Texture2D> tex, int height, int width, int frameCount);
		void SetSpeed(float newSpeed);


	private:
		GameObject* m_pParent;
		std::map <State, std::shared_ptr<Texture2D>> m_StateTextureMap;
		std::map <State, int> m_StateFrameHeight;
		std::map <State, int> m_StateFrameWidth;
		std::map <State, int> m_StateFrameCount;

		State m_previousState;

		// how many seconds it takes to go to the next frame
		float m_Speed;

		// keeping the count of time 
		float m_animTimer;

		// keeping the count of the frame
		int m_frameCount;

	};
}


