//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include "ERenderer.h"

// General includes
#include "structs.h"
#include <future>

// Features includes
#include "Scenegraph.h"
#include "Camera.h"
#include "Primitive.h"
#include "Material.h"
#include "Light.h"

// Multithreading
// Reference: https://medium.com/@phostershop/solving-multithreaded-raytracing-issues-with-c-11-7f018ecd76fa
//#define SINGLE_THREAD
#define MULTI_THREAD

Elite::Renderer::Renderer(SDL_Window* pWindow)
			   : m_RenderState{ false, false, true }				
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render(const Scenegraph* pScenegraph, Camera* pCamera)
{
	SDL_LockSurface(m_pBackBuffer);

	#ifdef SINGLE_THREAD
	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			RaytracePixel(r, c, pScenegraph->GetPrimitives(), pScenegraph->GetLights(), pScenegraph->GetMaterials(), pCamera);

			//FIll the backbuffer with the colorToFill in the HitRecord
			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(m_Hitrecord.colorToFill.r * 255.f),
				static_cast<uint8_t>(m_Hitrecord.colorToFill.g * 255.f),
				static_cast<uint8_t>(m_Hitrecord.colorToFill.b * 255.f));
		}
	}
	#endif // SINGLE_THREAD
	#ifdef MULTI_THREAD
	std::size_t cores = std::thread::hardware_concurrency();
	uint32_t maxPixels = m_Width * m_Height;
	uint32_t maxPixelsEachCore = maxPixels / (uint32_t)cores;
	std::vector<std::future<void>> future_vector;
	
	for (std::size_t i{0}; i < cores; ++i)
	{
		future_vector.emplace_back(std::async([i, &pScenegraph, maxPixelsEachCore, this, maxPixels]()
		{
			size_t currentPixelForThisCore{ i * maxPixelsEachCore };
			size_t maxPixelsForThisCore{ (i + 1) * maxPixelsEachCore };
			
			for (std::size_t index{ currentPixelForThisCore }; index < maxPixelsForThisCore && index < maxPixels; ++index)
			{
				uint32_t x = (uint32_t)index % m_Width;
				uint32_t y = (uint32_t)index / m_Width;
				RaytracePixel(y, x, pScenegraph->GetPrimitives(), pScenegraph->GetLights(), pScenegraph->GetMaterials(), pScenegraph->GetCamera(), index);
			}
		}));
	}	

	for (size_t i{}; i < future_vector.size(); ++i)
	{
		future_vector[i].wait();
	}
	#endif // MULTI_THREAD

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

void Elite::Renderer::RaytracePixel(const uint32_t& r, const uint32_t& c, const std::vector<Primitive*>& pPrimitives, const std::vector<Light*>& pLights, const std::vector<Material*>& pMaterials, Camera* camera, const std::size_t index)
{
	Ray rayCam{};
	HitRecord hitRecord{};
	camera->ConstructRay(rayCam, c, r);

	// Loop over all the objects in the scene
	size_t primitivesSize{ pPrimitives.size() };
	for (size_t i{}; i < primitivesSize; ++i)
	{
		if (pPrimitives[i]->Hit(rayCam, hitRecord, true))
		{
			// Check if the new hit is closer then the previous hit
			if (hitRecord.t < hitRecord.tClosest)
			{
				// Remember the closest t for future reference to compare to each other
				hitRecord.tClosest = hitRecord.t;

				RenderShading(i, pPrimitives, pLights, pMaterials, hitRecord, rayCam);
				
				if (hitRecord.colorToFill.r > 1.f ||
					hitRecord.colorToFill.g > 1.f ||
					hitRecord.colorToFill.b > 1.f)
					hitRecord.colorToFill.MaxToOne();

				// FIll the backbuffer with the colorToFill in the HitRecord
				m_pBackBufferPixels[index] = SDL_MapRGB(m_pBackBuffer->format,
					static_cast<uint8_t>(hitRecord.colorToFill.r * 255.f),
					static_cast<uint8_t>(hitRecord.colorToFill.g * 255.f),
					static_cast<uint8_t>(hitRecord.colorToFill.b * 255.f));
			}
		}
	}
}
void Elite::Renderer::RenderShading(const size_t index, const std::vector<Primitive*>& pPrimitives, const std::vector<Light*>& pLights, const std::vector<Material*>& pMaterials, HitRecord& hitRecord, const Ray& rayCam)
{
	///* Manage materials */
	//pMaterials[index]->SetDiffuseColor(hitRecord.color);

	// Loop over all the lights and calculate the finalColor
	hitRecord.colorToFill = Elite::RGBColor(0, 0, 0);
	size_t LightsSize{ pLights.size() };
	size_t primitivesSize{ pPrimitives.size() };
	for (size_t i{}; i < LightsSize; ++i)
	{
		Elite::FVector3 lightDir{ pLights[i]->GetDirectionShadow(hitRecord.point) };		// Not normalized, normalizing happens on line 147;
		if (m_RenderState.useShadows)
		{
			Ray rayShadows{};
			rayShadows.origin = hitRecord.point + (hitRecord.normal * 0.001f);
			rayShadows.tMax = Elite::Normalize(lightDir);
			rayShadows.direction = lightDir;

			bool lightCanSeePoint{ false };
			for (size_t j{}; j < primitivesSize; ++j)
			{
				if (pPrimitives[j]->Hit(rayShadows, hitRecord, false))
				{
					lightCanSeePoint = false;
					break;
				}
				else
					lightCanSeePoint = true;
			}

			if (lightCanSeePoint)
			{
				ShadePixel(index, i, pLights, pMaterials, lightDir, hitRecord, rayCam);
			}
		}
		else
		{	
			ShadePixel(index, i, pLights, pMaterials, Elite::GetNormalized(lightDir), hitRecord, rayCam);
		}
	}
}

void Elite::Renderer::ShadePixel(const size_t index, const size_t lightIndex, const std::vector<Light*>& pLights, const std::vector<Material*>& pMaterials, const Elite::FVector3& lightDir, HitRecord& hitRecord, const Ray& rayCam)
{
	if (m_RenderState.useIrradianceOnly)
		hitRecord.colorToFill += pLights[lightIndex]->CalculateIrradiance(hitRecord);
	else if (m_RenderState.useBRDFOnly)
	{
		Elite::FVector3 viewDir{ rayCam.direction };
		Elite::RGBColor BRDF{ pMaterials[index]->Shade(hitRecord, lightDir, -viewDir) };

		hitRecord.colorToFill += BRDF;
	}
	else if (!m_RenderState.useIrradianceOnly && !m_RenderState.useBRDFOnly)
	{
		Elite::FVector3 viewDir{ rayCam.direction };
		Elite::RGBColor BRDF{ pMaterials[index]->Shade(hitRecord, lightDir, -viewDir) };

		hitRecord.colorToFill += (pLights[lightIndex]->CalculateIrradiance(hitRecord) * BRDF);
	}
}