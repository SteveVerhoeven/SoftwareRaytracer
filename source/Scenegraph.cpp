#include "Scenegraph.h"

// Features includes
#include "structs.h"
#include "Camera.h"
#include "Primitive.h"
#include "Light.h"
#include "Material.h"

// Extra includes
#include <vector>
#include <iostream>

// Elite includes
#include "ETimer.h"

// SDL includes
#include "SDL.h"

Scenegraph::Scenegraph(Elite::Timer* pTimer)
		  : m_pPrimitives{ std::vector<Primitive*>() }
		  , m_pLights{ std::vector<Light*>() }
		  , m_pMaterials{ std::vector<Material*>() }
		  , m_pCamera{ nullptr }
{}
Scenegraph::~Scenegraph()
{
	DELETEPOINTERS(m_pPrimitives, m_pPrimitives.size());
	DELETEPOINTERS(m_pLights, m_pLights.size());
	DELETEPOINTERS(m_pMaterials, m_pMaterials.size());
	DELETEPOINTER(m_pCamera);
}

void Scenegraph::Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, Elite::Renderer* pRenderer)
{
	// Initialize variables for future reference
	m_pCamera = new Camera(Elite::FPoint3(0, 3.5f, 11), 45);
	m_pCamera->Initialize(screenWidth, screenHeight);
}
void Scenegraph::Update(const float elapsedSec)
{
	UpdateTriangles(elapsedSec);
}
void Scenegraph::UpdateTriangles(const float elapsedSec)
{
	size_t primSize{ m_pPrimitives.size() };
	for (size_t i{}; i < primSize; ++i)
		m_pPrimitives[i]->Update(elapsedSec);
}