#pragma once
#include <vector>

class Light;
class Camera;
class Scenegraph;
namespace Elite
{
	class Renderer;
}
class InputManager final
{
	public:
		InputManager() = default;
		~InputManager() = default;

		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) noexcept = delete;
		InputManager& operator=(const InputManager&) = delete;
		InputManager& operator=(InputManager&&) noexcept = delete;

		void Initialize();
		int Update(const float elapsedSec, Scenegraph* pScenegraph, Elite::Renderer* pRenderer, const int activeSceneIndex, bool& isLooping, bool& takeScreenshot);

	private:
		bool m_DelayTime;
		float m_CurrentDelayTime, m_MaxDelayTime;

		int UpdateScenes(const int activeSceneIndex);
		void UpdateCamera(const float elapsedSec, Camera* pCamera);
		void UpdateLights(const std::vector<Light*>& pLights, Elite::Renderer* pRenderer);
		void UpdateShadows(Elite::Renderer* pRenderer);

		void DelayInput(const float elapsedSec);
};