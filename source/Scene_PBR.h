#pragma once
#include "Scene.h"

class Scene_PBR final : public Scene
{
	public:
		Scene_PBR() = default;
		~Scene_PBR() = default;

		Scene_PBR(const Scene_PBR&) = delete;
		Scene_PBR(Scene_PBR&&) noexcept = delete;
		Scene_PBR& operator=(const Scene_PBR&) = delete;
		Scene_PBR& operator=(Scene_PBR&&) noexcept = delete;

		virtual void Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, SDL_Window* pWindow, Elite::Timer* pTimer) override;
		virtual void Update(const float elapsedSec) override;
		virtual void Render() override;

	protected:
	private:
		virtual void CreateScene() override;
};