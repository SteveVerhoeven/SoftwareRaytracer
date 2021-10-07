#include "InputManager.h"

// External includes
#include "SDL.h"

// Features includes
#include "Camera.h"
#include "Light.h"
#include "Scenegraph.h"

// General includes
#include <iostream>

// Elite includes
#include "ERenderer.h"

void InputManager::Initialize()
{
	m_DelayTime = false;
	m_CurrentDelayTime = 0;
	m_MaxDelayTime = 0.5f;
}

int InputManager::Update(const float elapsedSec, Scenegraph* pScenegraph, Elite::Renderer* pRenderer, const int activeSceneIndex, bool& isLooping, bool& takeScreenshot)
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				if (e.key.keysym.scancode == SDL_SCANCODE_X)
					takeScreenshot = true;
				break;
		}
	}

	auto lights{ pScenegraph->GetLights() };
	UpdateCamera(elapsedSec, pScenegraph->GetCamera());
	UpdateLights(pScenegraph->GetLights(), pRenderer);
	UpdateShadows(pRenderer);

	if (m_DelayTime)
		DelayInput(elapsedSec);

	return UpdateScenes(activeSceneIndex);
}

void InputManager::UpdateCamera(const float elapsedSec, Camera* pCamera)
{
	int x{}, y{};
	float inputMultiplier = 20.f;
	const Uint32 mouseState = SDL_GetRelativeMouseState(&x, &y);

	if (SDL_BUTTON(1) == mouseState)		// LB
	{
		pCamera->MoveForward(y * elapsedSec, x * elapsedSec);
	}
	else if (SDL_BUTTON(3) == mouseState)	// RB
	{
		float xAngle = (float(x) * inputMultiplier * elapsedSec) * float(E_TO_RADIANS);
		float yAngle = (float(y) * inputMultiplier * elapsedSec) * float(E_TO_RADIANS);

		pCamera->MoveRotation(-xAngle, -yAngle);
	}
	else if ((SDL_BUTTON(1) + SDL_BUTTON(3)) == mouseState)		// LB + RB
	{
		pCamera->MoveUp(float(y * elapsedSec));
	}
}

void InputManager::UpdateLights(const std::vector<Light*>& pLights, Elite::Renderer* pRenderer)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// J: enable/disable directional light
	if (state[SDL_SCANCODE_J] && !m_DelayTime)
	{
		pLights[2]->SetIsBurning(!pLights[2]->GetIsBurning());
		m_DelayTime = true;
	}
	// K - L : enable / disable left right point light
	else if (state[SDL_SCANCODE_K] && !m_DelayTime)
	{
		pLights[0]->SetIsBurning(!pLights[0]->GetIsBurning());
		m_DelayTime = true;
	}
	else if (state[SDL_SCANCODE_L] && !m_DelayTime)
	{
		pLights[1]->SetIsBurning(!pLights[1]->GetIsBurning());
		m_DelayTime = true;
	}
	// T: toggle between Irradiance only, BRDF only and all combined. Lambert’s Cosine Law is always used.
	else if (state[SDL_SCANCODE_T] && !m_DelayTime)
	{
		if (!pRenderer->GetRenderState().useIrradianceOnly && !pRenderer->GetRenderState().useBRDFOnly)
		{
			pRenderer->SetRenderStateIrradiance(true);
			m_DelayTime = true;
		}
		else if (pRenderer->GetRenderState().useIrradianceOnly && !pRenderer->GetRenderState().useBRDFOnly)
		{
			pRenderer->SetRenderStateIrradiance(false);
			pRenderer->SetRenderStateBRDF(true);
			m_DelayTime = true;
		}
		else if (!pRenderer->GetRenderState().useIrradianceOnly && pRenderer->GetRenderState().useBRDFOnly)
		{
			pRenderer->SetRenderStateBRDF(false);
			m_DelayTime = true;
		}
	}
}
void InputManager::UpdateShadows(Elite::Renderer* pRenderer)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// Z: enable/disable hard shadows
	if (state[SDL_SCANCODE_Z] && !m_DelayTime)
	{
		pRenderer->SetRenderStateShadows(!pRenderer->GetRenderState().useShadows);
		m_DelayTime = true;
	}
}
int InputManager::UpdateScenes(const int activeSceneIndex)
{
	const Uint8* state = SDL_GetKeyboardState(NULL);
	// S: Switch scene
	if (state[SDL_SCANCODE_S] && !m_DelayTime)
	{
		m_DelayTime = true;
		
		if (activeSceneIndex == 0)
			return 1;
		else if(activeSceneIndex == 1)
			return 0;
	}

	return activeSceneIndex;
}

void InputManager::DelayInput(const float elapsedSec)
{
	if (m_CurrentDelayTime > m_MaxDelayTime)
	{
		m_CurrentDelayTime = 0;
		m_DelayTime = false;
	}
	else
		m_CurrentDelayTime += elapsedSec;
}