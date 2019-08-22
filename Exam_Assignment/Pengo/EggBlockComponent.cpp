#include "pch.h"
#include "EggBlockComponent.h"

dae::EggBlockComponent::EggBlockComponent(GameObject * parent, GameObject * gameGridObj, Scene& sceneRef)
	: BaseComponent(parent)
	, m_SceneRef(sceneRef)
	, mp_gameGridObj(gameGridObj)
{
}

dae::EggBlockComponent::~EggBlockComponent()
{

}

void dae::EggBlockComponent::Update(const float & deltaTime)
{
	if (m_isShowing)
	{
		// handle timer
		m_timer += deltaTime;
		if (m_timer > m_showTime)
		{
			// reset variables
			m_isShowing = false;
			m_timer = 0.0f;

			// put the texture back
			m_pParent->GetComponent<TextureComponent>()->SetTexture("IceBlock.png");
			m_pParent->GetComponent<TextureComponent>()->SetWidthAndHeight(32, 32);
			m_pParent->GetComponent<TextureComponent>()->SetIsAnimated(false);
		}
	}
}

void dae::EggBlockComponent::Render() const
{

}

void dae::EggBlockComponent::Hatch(int positionIdx)
{

	// create a new sno bee, just like the level loader does it
	// give components
	GameObject* snoBee = new GameObject();
	// -- texture
	snoBee->AddComponent(new TextureComponent(snoBee));
	snoBee->GetComponent<TextureComponent>()->SetIsAnimated(true);

	// -- animator
	snoBee->AddComponent(new dae::AnimatorComponent(snoBee));
	snoBee->GetComponent<AnimatorComponent>()->SetSpeed(0.5f);

	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkLeft.png"), 16, 16, 2);
	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkRight.png"), 16, 16, 2);
	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkDown.png"), 16, 16, 2);
	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::FACING_UP, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeWalkUp.png"), 16, 16, 2);

	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_LEFT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigLeft.png"), 16, 16, 2);
	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_RIGHT, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigRight.png"), 16, 16, 2);
	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_DOWN, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigDown.png"), 16, 16, 2);
	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::DIGGING_UP, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeDigUp.png"), 16, 16, 2);

	snoBee->GetComponent<AnimatorComponent>()->AddAnimation(State::STRUGGLING, dae::ResourceManager::GetInstance().LoadTexture("GreenBeeStruggle.png"), 16, 16, 2);

	// -- brainnnz
	snoBee->AddComponent(new StateComponent(snoBee, false));

	snoBee->AddComponent(new SnoBeeAIComponent(snoBee, Point2f{ 16,16 }, 2.0f, mp_gameGridObj));
	snoBee->GetComponent<SnoBeeAIComponent>()->SetPosition(positionIdx);


}

void dae::EggBlockComponent::Show(float time)
{
	// set time variables
	m_showTime = time;
	m_timer = 0.0f;

	// change Boolean
	m_isShowing = true;

	// change texture
	m_pParent->GetComponent<TextureComponent>()->SetIsAnimated(true);
	m_pParent->GetComponent<AnimatorComponent>()->AddAnimation(State::IDLE, dae::ResourceManager::GetInstance().LoadTexture("EggBlock.png"), 16, 16, 2);
	m_pParent->GetComponent<AnimatorComponent>()->SetSpeed(0.2f);
}
