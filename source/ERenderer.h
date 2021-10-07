/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

#include <cstdint>
#include "structs.h"
#include <vector>

struct SDL_Window;
struct SDL_Surface;
class Camera;
class Scenegraph;
class Primitive;
class Light;
class Material;
namespace Elite
{
	class Renderer final
	{
		public:
			Renderer(SDL_Window* pWindow);
			~Renderer() = default;

			Renderer(const Renderer&) = delete;
			Renderer(Renderer&&) noexcept = delete;
			Renderer& operator=(const Renderer&) = delete;
			Renderer& operator=(Renderer&&) noexcept = delete;

			void Render(const Scenegraph* pScenegraph, Camera* camera);
			bool SaveBackbufferToImage() const;

			const RenderState& GetRenderState() const { return m_RenderState; }
			void SetRenderStateIrradiance(bool useIrrdianceOnly) { m_RenderState.useIrradianceOnly = useIrrdianceOnly; }
			void SetRenderStateBRDF(bool useBRDFOnly) { m_RenderState.useBRDFOnly = useBRDFOnly; }
			void SetRenderStateShadows(bool useShadows) { m_RenderState.useShadows = useShadows; }

		private:
			SDL_Window* m_pWindow = nullptr;
			SDL_Surface* m_pFrontBuffer = nullptr;
			SDL_Surface* m_pBackBuffer = nullptr;
			uint32_t* m_pBackBufferPixels = nullptr;
			uint32_t m_Width = 0;
			uint32_t m_Height = 0;

			RenderState m_RenderState;

			void RaytracePixel(const uint32_t& r, const uint32_t& c, const std::vector<Primitive*>& pPrimitives, const std::vector<Light*>& pLights, const std::vector<Material*>& pMaterials, Camera* camera, const std::size_t index);
	
			void RenderShading(const size_t index, const std::vector<Primitive*>& pPrimitives, const std::vector<Light*>& pLights, const std::vector<Material*>& pMaterials, HitRecord& hitRecord, const Ray& ray);
			void ShadePixel(const size_t indexHit, const size_t lightIndex, const std::vector<Light*>& pLights, const std::vector<Material*>& pMaterials, const Elite::FVector3& lightDir, HitRecord& hitRecord, const Ray& ray);
	};
}
#endif