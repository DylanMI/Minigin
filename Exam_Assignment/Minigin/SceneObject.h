#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void Update(const float& deltaTime) = 0;
		virtual void Render() const = 0;

		SceneObject() = default;
		~SceneObject();
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	};
}
