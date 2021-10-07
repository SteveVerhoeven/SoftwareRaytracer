#pragma once
#include <vector>

class Scene;
struct SDL_Window;
class InputManager;
namespace Elite
{
	class Timer;
}
class Raytracer final
{
	public:
		Raytracer();
		~Raytracer();

		Raytracer(const Raytracer&) = delete;
		Raytracer(Raytracer&&) noexcept = delete;
		Raytracer& operator=(const Raytracer&) = delete;
		Raytracer& operator=(Raytracer&&) noexcept = delete;

		void Initialize(Elite::Timer* pTimers, SDL_Window* pWindow, const uint32_t screenWidth, const uint32_t screenHeight);
		void Update(const float elapsedSec, bool& isLooping, bool& takeScreenshot);
		void Render();

		Scene* GetActiveScene() const { return m_pScenes[m_ActiveSceneIndex]; };

	protected:
	private:
		int m_ActiveSceneIndex;
		InputManager* m_pInputManager;
		std::vector<Scene*> m_pScenes;

		void OutputKeyInputs();
};