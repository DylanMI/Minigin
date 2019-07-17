#include "MiniginPCH.h"
#include "AnimatorComponent.h"


dae::AnimatorComponent::AnimatorComponent(GameObject * parent)
	: BaseComponent(parent)
{
	m_previousState = State::IDLE;
}

dae::AnimatorComponent::~AnimatorComponent()
{
	m_pParent = nullptr;
	delete m_pParent;
}

void dae::AnimatorComponent::Update(const float & deltaTime)
{
	// get the current state from the parent
	State placeholderState = m_pParent->GetComponent<StateComponent>()->GetState();

	// if the state is different from the previous one, reset the timer and the counter
	// else just continue
	if (placeholderState != m_previousState)
	{
		// reset counter and timer
		m_frameCount = 0;
		m_animTimer = 0.0f;

		m_previousState = placeholderState;
	}

	// update the time
	m_animTimer += deltaTime;

	// check if the timer is over the limit
	if (m_animTimer > m_Speed)
	{
		m_animTimer = 0.0f;
		// if so increment to next texture
		m_frameCount++;
	}
	// if the framecount is over the max
	if (m_frameCount >= m_StateFrameCount[m_previousState])
	{
		m_frameCount = 0;
	}

	// send the information to the TextureComponent
	
	SDL_Rect srcrect;
	srcrect.x = m_frameCount * m_StateFrameWidth[m_previousState];
	srcrect.y = 0;
	srcrect.w = m_StateFrameWidth[m_previousState];
	srcrect.h = m_StateFrameHeight[m_previousState];
	m_pParent->GetComponent<dae::TextureComponent>()->SetAnimatedSourceRect(srcrect);
	m_pParent->GetComponent<dae::TextureComponent>()->SetTexture(m_StateTextureMap[m_previousState]);

}

void dae::AnimatorComponent::Render() const
{
}

void dae::AnimatorComponent::AddAnimation(State CharacterState, std::shared_ptr<Texture2D> tex, int height, int width, int frameCount)
{
	m_StateTextureMap[CharacterState] = tex;
	m_StateFrameCount[CharacterState] = frameCount;
	m_StateFrameHeight[CharacterState] = height;
	m_StateFrameWidth[CharacterState] = width;

}

void dae::AnimatorComponent::SetSpeed(float newSpeed)
{
	m_Speed = newSpeed;
}
