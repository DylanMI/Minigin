#pragma once
namespace dae
{
	class BaseComponent abstract
	{
	public:

		virtual void Update(const float& deltaTime) = 0;
		virtual void Render() const = 0;


		BaseComponent() = default;
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;
	};
}


