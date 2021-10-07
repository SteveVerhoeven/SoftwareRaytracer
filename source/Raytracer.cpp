#include "Raytracer.h"

// General includes
#include <vector>
#include <iostream>

// External includes
#include "SDL.h"

// Features includes
#include "Scene_PBR.h"
#include "Scene_Bunny.h"
#include "InputManager.h"
#include "structs.h"

Raytracer::Raytracer()
		 : m_ActiveSceneIndex{}
		 , m_pInputManager{ nullptr }
		 , m_pScenes{ std::vector<Scene*>() }
{}
Raytracer::~Raytracer()
{
	DELETEPOINTER(m_pInputManager);
	DELETEPOINTERS(m_pScenes, m_pScenes.size());
}

void Raytracer::Initialize(Elite::Timer* pTimer, SDL_Window* pWindow, const uint32_t screenWidth, const uint32_t screenHeight)
{
	m_ActiveSceneIndex = 0;
	m_pInputManager = new InputManager();
	m_pInputManager->Initialize();

	Scene_PBR* pbrScene{ new Scene_PBR() };
	pbrScene->Initialize(screenWidth, screenHeight, pWindow, pTimer);
	m_pScenes.push_back(pbrScene);

	Scene_Bunny* bunnyScene{ new Scene_Bunny() };
	bunnyScene->Initialize(screenWidth, screenHeight, pWindow, pTimer);
	m_pScenes.push_back(bunnyScene);

	OutputKeyInputs();
}

void Raytracer::Update(const float elapsedSec, bool& isLooping, bool& takeScreenshot)
{
	m_ActiveSceneIndex = m_pInputManager->Update(elapsedSec, m_pScenes[m_ActiveSceneIndex]->GetSceneGraph(), m_pScenes[m_ActiveSceneIndex]->GetRenderer(), m_ActiveSceneIndex, isLooping, takeScreenshot);
	m_pScenes[m_ActiveSceneIndex]->Update(elapsedSec);
}

void Raytracer::Render()
{
	m_pScenes[m_ActiveSceneIndex]->Render();
}

void Raytracer::OutputKeyInputs()
{
	std::cout << "+<==========================================>+\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|| Raytracer: Steve Verhoeven - 2DAE02      ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "||                Input keys                ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|| Take screenshot: X                       ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|| Change scene: S                          ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|| Enable / Disable - Left point light: K   ||\n";
	std::cout << "|| Enable / Disable - Right point light: L  ||\n";
	std::cout << "|| Enable / Disable - Directional light: J  ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|| Enable / Disable - Shadows: Z            ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "|| Switch between: T                        ||\n";
	std::cout << "|| - Irradiance only:                       ||\n";
	std::cout << "|| - BRDF only:                             ||\n";
	std::cout << "|| - ALL combined:                          ||\n";
	std::cout << "|<------------------------------------------>|\n";
	std::cout << "+<==========================================>+\n";
}