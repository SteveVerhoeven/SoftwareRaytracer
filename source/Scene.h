#pragma once
#include <cstdint>

class Scenegraph;
class Camera;
struct SDL_Window;
namespace Elite
{
	class Timer;
	class Renderer;
}
class Scene
{
	public:
		Scene();
		~Scene();

		Scene(const Scene&) = delete;
		Scene(Scene&&) noexcept = delete;
		Scene& operator=(const Scene&) = delete;
		Scene& operator=(Scene&&) noexcept = delete;

		virtual void Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, SDL_Window* pWindow, Elite::Timer* pTimer);
		virtual void Update(const float elapsedSec) = 0;
		virtual void Render() = 0;

		virtual Scenegraph* GetSceneGraph() const { return m_pSceneGraph; };
		virtual Elite::Renderer* GetRenderer() const { return m_pERenderer; };

	protected:
		Scenegraph* m_pSceneGraph;
		Elite::Renderer* m_pERenderer;
		
		virtual void CreateScene() = 0;

	private:

};