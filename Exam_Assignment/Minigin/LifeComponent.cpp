#include "MiniginPCH.h"
#include "LifeComponent.h"

dae::LifeComponent::LifeComponent(GameObject * parent, LifeObserver * lifeObserver)
	: BaseComponent(parent)
	,m_lifeObserver(lifeObserver)
	,m_prevLife(3)
{
}

void dae::LifeComponent::Update(const float & )
{	
	// get the life from the observer,
	int life = m_lifeObserver->GetLives();
	
	// tell the parents textrenderer what to render
	if (m_prevLife != life)
	{
		m_pParent->GetComponent<TextRendererComponent>()->ChangeText(std::string("LIVES: ") + std::to_string(life));
		m_prevLife = life;
	}

	// check if all lifes are empty
	if (m_lifeObserver->GetIsDead())
	{
		// do something
		m_prevLife = 3;
	}
}

void dae::LifeComponent::Render() const
{
}
