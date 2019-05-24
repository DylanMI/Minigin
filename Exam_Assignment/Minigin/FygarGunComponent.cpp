#include "MiniginPCH.h"
#include "FygarGunComponent.h"

dae::FygarGunComponent::FygarGunComponent(GameObject * parent, Scene & scene)
	: m_pParent(parent)
	, m_scene(scene)
	, m_canShoot(true)
	, m_shootCooldownTimer(m_shootCooldownTime)
{
}

void dae::FygarGunComponent::Update(const float & deltaTime )
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

void dae::FygarGunComponent::Render() const
{
}

void dae::FygarGunComponent::Shoot(Point2f direction)
{
	// make a gun object, direction, time etc...
	auto bullet = new GameObject();
	bullet->AddComponent(new TextureComponent(bullet));
	bullet->AddComponent(new CollisionComponent(bullet));

	bullet->GetComponent<CollisionComponent>()->SetTag(collisionTag::Fire);

	// set texture according to given Direction

	// left
	if (direction.x == Point2f{-1,0}.x && direction.y == Point2f{ -1,0 }.y)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Fire_Left.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x - 48, m_pParent->GetTransform().GetPosition().y + 16 });
		bullet->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{ 48,16 });

	}

	// right
	if (direction.x == Point2f{ 1,0 }.x && direction.y == Point2f{ 1,0 }.y)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Fire_Right.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x + 48, m_pParent->GetTransform().GetPosition().y + 16 });
		bullet->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{ 48,16 });
	}

	// up
	if (direction.x == Point2f{ 0,1 }.x && direction.y == Point2f{ 0,1 }.y)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Fire_Up.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x + 16 , m_pParent->GetTransform().GetPosition().y - 32 });
		bullet->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{ 16,48 });
	}

	// down
	if (direction.x == Point2f{ 0,-1 }.x && direction.y == Point2f{ 0,-1 }.y)
	{
		bullet->GetComponent<TextureComponent>()->SetTexture(dae::ResourceManager::GetInstance().LoadTexture("Fire_Down.png"));
		bullet->SetPosition(Point2f{ m_pParent->GetTransform().GetPosition().x + 16, m_pParent->GetTransform().GetPosition().y + 32 });
		bullet->GetComponent<CollisionComponent>()->SetWidthAndHeight(Point2f{ 16,48 });
	}
	// make it kill itslef after a certain time
	bullet->AddComponent(new DeleteSelfComponent(bullet, m_scene));
	bullet->GetComponent<DeleteSelfComponent>()->StartSelfDestruct(0.5f);

	// add it to the scene
	m_scene.Add(bullet);
	CollisionManager::GetInstance().RegisterCollisionObject(bullet);

	m_canShoot = false;
}

bool dae::FygarGunComponent::GetCanShoot()
{
	return m_canShoot;
}

