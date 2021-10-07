#pragma once
#include "Scene.h"

class Scene_Bunny final : public Scene
{
	public:
		Scene_Bunny() = default;
		~Scene_Bunny() = default;

		Scene_Bunny(const Scene_Bunny&) = delete;
		Scene_Bunny(Scene_Bunny&&) noexcept = delete;
		Scene_Bunny& operator=(const Scene_Bunny&) = delete;
		Scene_Bunny& operator=(Scene_Bunny&&) noexcept = delete;

		virtual void Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, SDL_Window* pWindow, Elite::Timer* pTimer) override;
		virtual void Update(const float elapsedSec) override;
		virtual void Render() override;

	protected:
	private:
		virtual void CreateScene() override;
};