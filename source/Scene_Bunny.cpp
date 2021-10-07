#include "Scene_Bunny.h"

// Elite Includes
#include "ERenderer.h"
#include "ETimer.h"

// Scene Includes
#include "Scenegraph.h"
// Scene objects includes
#include "Primitive.h"
#include "PPlane.h"
#include "TriangleMesh.h"
// Scene lights includes
#include "LDirectional.h"
#include "LPoint.h"
// Scene materials includes
#include "MLambert.h"

void Scene_Bunny::Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, SDL_Window* pWindow, Elite::Timer* pTimer)
{
	Scene::Initialize(screenWidth, screenHeight, pWindow, pTimer);

	CreateScene();
}
void Scene_Bunny::Update(const float elapsedSec)
{
	m_pSceneGraph->Update(elapsedSec);
}
void Scene_Bunny::Render()
{
	m_pERenderer->Render(m_pSceneGraph, m_pSceneGraph->GetCamera());
}

void Scene_Bunny::CreateScene()
{
	Elite::RGBColor white{ 1.f, 1.f, 1.f };
	Elite::RGBColor black{ 0.f, 0.f, 0.f };
	Elite::RGBColor pewterBlue{ 0.6157f, 0.7020f, 0.7294f };
	Elite::RGBColor oldRose{ 0.7255f, 0.5137f, 0.5372f };
	Elite::RGBColor paleSilver{ 0.7451f, 0.7216f, 0.7059f };

	// Mesh
	TriangleMesh* tMesh = new TriangleMesh(Primitive::CullMode::BACK_FACE, oldRose);
	tMesh->Initialize();
	m_pSceneGraph->AddPrimitiveToGraph(tMesh);
	m_pSceneGraph->AddMaterialToGraph(new MLambert(1.f, oldRose));

	// Planes
	m_pSceneGraph->AddPrimitiveToGraph(new PPlane(Elite::FPoint3(0.f, -0.2f, 0.f), Elite::FVector3(0.f, 1.f, 0.f)));
	m_pSceneGraph->AddMaterialToGraph(new MLambert(1.f, paleSilver));
	m_pSceneGraph->AddPrimitiveToGraph(new PPlane(Elite::FPoint3(0.f, 0.f, -10.f), Elite::FVector3(0.f, 0.f, 1.f)));
	m_pSceneGraph->AddMaterialToGraph(new MLambert(1.f, paleSilver));
	m_pSceneGraph->AddPrimitiveToGraph(new PPlane(Elite::FPoint3(-7.f, 0.f, 0.f), Elite::FVector3(1.f, 0.f, 0.f)));
	m_pSceneGraph->AddMaterialToGraph(new MLambert(1.f, paleSilver));
	m_pSceneGraph->AddPrimitiveToGraph(new PPlane(Elite::FPoint3(7.f, 0.f, 0.f), Elite::FVector3(-1.f, 0.f, 0.f)));
	m_pSceneGraph->AddMaterialToGraph(new MLambert(1.f, paleSilver));
	m_pSceneGraph->AddPrimitiveToGraph(new PPlane(Elite::FPoint3(0.f, 12.f, 0.f), Elite::FVector3(0.f, -1.f, 0.f)));
	m_pSceneGraph->AddMaterialToGraph(new MLambert(1.f, paleSilver));

	/* LIGHTS */
	m_pSceneGraph->AddLightToGraph(new LPoint(25, white, Elite::FVector3(0, 5.f, -7.f)));
	m_pSceneGraph->AddLightToGraph(new LPoint(25, white, Elite::FVector3(0, 2.5f, 5.f)));
	m_pSceneGraph->AddLightToGraph(new LDirectional(0.5f, white, Elite::FVector3(0, 0.77f, 0.77f)));
}