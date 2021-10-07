#pragma once
#include <vector>
#include "structs.h"

class Light;
class Camera;
class Primitive;
class Material;
namespace Elite
{
	class Renderer;
	class Timer;
}
class Scenegraph final
{
	public:
		Scenegraph(Elite::Timer* pTimer);
		~Scenegraph();

		Scenegraph(const Scenegraph&) = delete;
		Scenegraph(Scenegraph&&) noexcept = delete;
		Scenegraph& operator=(const Scenegraph&) = delete;
		Scenegraph& operator=(Scenegraph&&) noexcept = delete;

		void Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, Elite::Renderer* pRenderer);
		void Update(const float elapsedSec);

		// Functions
		void AddPrimitiveToGraph(Primitive* pPrimitive) { m_pPrimitives.push_back(pPrimitive); }
		void AddLightToGraph(Light* pLight) { m_pLights.push_back(pLight); }
		void AddMaterialToGraph(Material* pMaterial) { m_pMaterials.push_back(pMaterial); }

		const std::vector<Primitive*>& GetPrimitives() const { return m_pPrimitives; }
		const std::vector<Light*>& GetLights() const { return m_pLights; }
		const std::vector<Material*>& GetMaterials() const { return m_pMaterials; }

		Camera* GetCamera() const { return m_pCamera; }

	private:
		// Variables
		Camera* m_pCamera;
		std::vector<Primitive*> m_pPrimitives;
		std::vector<Light*> m_pLights;
		std::vector<Material*> m_pMaterials;

		void UpdateTriangles(const float elapsedSec);
};