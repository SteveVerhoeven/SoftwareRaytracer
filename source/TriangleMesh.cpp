#include "TriangleMesh.h"

#include "OBJParser.h"
#include "PTriangle.h"

/* -------------------------------------------------------------------------------------- */
/* (Un)comment to let hit function get triangles from a pre-defined vector with triangles */
/* -------------------------------------------------------------------------------------- */
//#define TRIANGLE_VECTOR		

TriangleMesh::TriangleMesh(const CullMode& cullMode, const Elite::RGBColor& color)
			: m_CullMode{ CullMode::BACK_FACE }
			, m_Color{ color }
			, m_Triangles{ std::vector<PTriangle*>() }
{}

void TriangleMesh::Initialize()
{
	OBJParser parser;
	parser.LoadModel("lowpoly_bunny", "./Resources/lowpoly_bunny.obj", m_VertexBuffer, m_IndexBuffer);
	
	#ifdef TRIANGLE_VECTOR
	// Code to work with vector of triangles instead of making them in hit function
	for (size_t i{}; i < m_IndexBuffer.size(); i += 3)
	{
		Vertex v0{ m_VertexBuffer[m_IndexBuffer[i + 0]] };
		Vertex v1{ m_VertexBuffer[m_IndexBuffer[i + 1]] };
		Vertex v2{ m_VertexBuffer[m_IndexBuffer[i + 2]] };

		m_Triangles.push_back(new PTriangle(v0, v1, v2, m_Color, m_CullMode));
	}
	#endif
}

void TriangleMesh::Update(const float elapsedSec)
{
}

bool TriangleMesh::Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const
{
	#ifndef TRIANGLE_VECTOR
	PTriangle triangle{Vertex(), Vertex(), Vertex(), m_CullMode};
	size_t indexBufferSize{ m_IndexBuffer.size() };
	for (size_t i{}; i < indexBufferSize; i += 3)
	{
		Vertex v0{ m_VertexBuffer[m_IndexBuffer[i + 0]] };
		Vertex v1{ m_VertexBuffer[m_IndexBuffer[i + 1]] };
		Vertex v2{ m_VertexBuffer[m_IndexBuffer[i + 2]] };

		triangle.Reinitialize(v0, v1, v2);
		if (triangle.Hit(ray, hitRecord, updateHitrecord))
			return true;
	}

	return false;
	#endif

	#ifdef TRIANGLE_VECTOR
	// Code to work with vector of triangles instead of making them in hit function
	size_t trianglesSize{ m_Triangles.size() };
	for (size_t i{}; i < trianglesSize; ++i)
	{
		if (m_Triangles[i]->Hit(ray, hitRecord, updateHitrecord))
			return true;
	}

	return false;
	#endif
}