#include "Scene_PBR.h"

// Elite Includes
#include "ERenderer.h"
#include "ETimer.h"

// Scene Includes
#include "Scenegraph.h"
// Scene Primitive includes
#include "PSphere.h"
#include "PPlane.h"
#include "PTriangle.h"
// Scene Light includes
#include "LDirectional.h"
#include "LPoint.h"
// Scene Material includes
#include "MLambert.h"
#include "MCookTorrance.h"

void Scene_PBR::Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight, SDL_Window* pWindow, Elite::Timer* pTimer)
{
	Scene::Initialize(screenWidth, screenHeight, pWindow, pTimer);

	CreateScene();
}
void Scene_PBR::Update(const float elapsedSec)
{
	m_pSceneGraph->Update(elapsedSec);
}
void Scene_PBR::Render()
{
	m_pERenderer->Render(m_pSceneGraph, m_pSceneGraph->GetCamera());
}

void Scene_PBR::CreateScene()
{
	Elite::RGBColor white{ 1.f, 1.f, 1.f };
	Elite::RGBColor black{ 0.f, 0.f, 0.f };
	Elite::RGBColor pewterBlue{ 0.6157f, 0.7020f, 0.7294f };
	Elite::RGBColor oldRose{ 0.7255f, 0.5137f, 0.5372f };
	Elite::RGBColor paleSilver{ 0.7451f, 0.7216f, 0.7059f };

	// Spheres
	// Buttom row: Left to Right
	m_pSceneGraph->AddPrimitiveToGraph(new PSphere(Elite::FPoint3(-2.5f, 1, 0.f), 1.f));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(true, 1.0f, oldRose));
	m_pSceneGraph->AddPrimitiveToGraph(new PSphere(Elite::FPoint3(0.f, 1, 0.f), 1.f));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(true, 0.6f, oldRose));
	m_pSceneGraph->AddPrimitiveToGraph(new PSphere(Elite::FPoint3(2.5f, 1, 0.f), 1.f));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(true, 0.1f, oldRose));
	// Top row: Left to Right
	m_pSceneGraph->AddPrimitiveToGraph(new PSphere(Elite::FPoint3(-2.5f, 3.2f, 0.f), 1.f));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(false, 1.0f, oldRose));
	m_pSceneGraph->AddPrimitiveToGraph(new PSphere(Elite::FPoint3(0.f, 3.2f, 0.f), 1.f));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(false, 0.6f, oldRose));
	m_pSceneGraph->AddPrimitiveToGraph(new PSphere(Elite::FPoint3(2.5f, 3.2f, 0.f), 1.f));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(false, 0.1f, oldRose));

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

	// Triangles
	m_pSceneGraph->AddPrimitiveToGraph(new PTriangle(Elite::FPoint3(-2.5f, 5.2f, 0.f), 1.5f, Primitive::CullMode::FRONT_FACE));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(false, 1.0f, oldRose));
	m_pSceneGraph->AddPrimitiveToGraph(new PTriangle(Elite::FPoint3(0.f, 5.2f, 0.f), 1.5f, Primitive::CullMode::NO_CULLING));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(false, 0.6f, oldRose));
	m_pSceneGraph->AddPrimitiveToGraph(new PTriangle(Elite::FPoint3(2.5f, 5.2f, 0.f), 1.5f, Primitive::CullMode::BACK_FACE));
	m_pSceneGraph->AddMaterialToGraph(new MCookTorrance(false, 0.1f, oldRose));

	/* LIGHTS */
	m_pSceneGraph->AddLightToGraph(new LPoint(25, paleSilver, Elite::FVector3(0, 7.5f, -7.5f)));
	m_pSceneGraph->AddLightToGraph(new LPoint(25, paleSilver, Elite::FVector3(0, 3.5f, 5.f)));
	m_pSceneGraph->AddLightToGraph(new LDirectional(0.9f, paleSilver, Elite::FVector3(0, 0.77f, 0.77f)));
}