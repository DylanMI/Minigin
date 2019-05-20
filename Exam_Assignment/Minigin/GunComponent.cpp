#include "MiniginPCH.h"
#include "GunComponent.h"

dae::GunComponent::GunComponent(GameObject * parent, Scene& scene)
	: m_pParent(parent)
	, m_scene(scene)
	, m_canShoot(true)
	, m_shootCooldownTimer(m_shootCooldownTime)
{
}

void dae::GunComponent::Update(const float & deltaTime)
{
	if (m_canShoot == false)
	{
		m_shootCooldownTimer -= deltaTime;
		if (m_shootCooldownTimer < 0.0f)
		{
			m_canShoot = true;
			m_shootCooldownTimer = m_shootCooldownTime;
		}
	}
}

void dae::GunComponent::Render() const
{
}

void dae::GunComponent::Shoot()
{
	// make a gun object, direction, time etc...
	auto bullet = new GameObject();
	bullet->AddComponent(new TextureComponent(bullet));
	// set texture according to Object orientation state
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::LEFT)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("DigDugWireLeft.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x - 32, m_pParent->GetTransform().GetPosition().y });
	}
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::RIGHT)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("DigDugWireRight.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x + 16, m_pParent->GetTransform().GetPosition().y });
	}
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::UP)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("DigDugWireUp.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x , m_pParent->GetTransform().GetPosition().y - 16});
	}
	if (m_pParent->GetComponent<StateComponent>()->GetState() == State::DOWN)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("DigDugWireDown.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x + 16, m_pParent->GetTransform().GetPosition().y + 32 });
	}

	// make it kill itslef after a certain time
	bullet->AddComponent(new DeleteSelfComponent(bullet, m_scene));
	bullet->GetComponent<DeleteSelfComponent>()->StartSelfDestruct(0.5f);

	// add it to the scene
	m_scene.Add(bullet);

	m_canShoot = false;
}

bool dae::GunComponent::GetCanShoot()
{
	return m_canShoot;
}
