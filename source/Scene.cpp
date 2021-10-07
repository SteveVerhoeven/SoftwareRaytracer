#include "Scene.h"
#include "Scenegraph.h"
#include "ERenderer.h"

Scene::Scene()
	: m_pERenderer{ nullptr }
	, m_pSceneGraph{ nullptr }
{}

Scene::~Scene()
{
	DELETEPOINTER(m_pERenderer);
	DELETEPOINTER(m_pSceneGraph);
}

void Scene::Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, SDL_Window* pWindow, Elite::Timer* pTimer)
{
	m_pERenderer = new Elite::Renderer(pWindow);
	m_pSceneGraph = new Scenegraph(pTimer);
	m_pSceneGraph->Initialize(screenWidth, screenHeight, m_pERenderer);
}