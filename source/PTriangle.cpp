#include "PTriangle.h"
#include "structs.h"

PTriangle::PTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const CullMode& cullMode, const Elite::RGBColor& color)
		 : m_Vertices{ v0, v1, v2 }
		 , m_Color(color)
		 , m_CullMode(cullMode)
{
	Elite::FVector3 a{ m_Vertices[1].position - m_Vertices[0].position };
	Elite::FVector3 b{ m_Vertices[2].position - m_Vertices[0].position };
	m_Normal = GetNormalized(Elite::Cross(a, b));
}

PTriangle::PTriangle(const Elite::FPoint3& origin, const float width, const CullMode& cullMode, const Elite::RGBColor& color)
		 : m_Origin{ origin }
		 , m_Color{ color }
		 , m_CullMode{ cullMode }
		 , m_Vertices{ 3 }
		 , m_Width{ width }
		 , m_NmrOfVertices{ 3 }
		 , m_RotationSpeed{ 1.f }
{
	CreateVertices();

	Elite::FVector3 a{ m_Vertices[1].position - m_Vertices[0].position };
	Elite::FVector3 b{ m_Vertices[2].position - m_Vertices[0].position };
	m_Normal = Elite::GetNormalized(Elite::Cross(a, b));

	Elite::FVector3 ToWorldOrigin{ -m_Origin.x, 0, 0 };
	Elite::FVector3 ToModelOrigin{ m_Origin.x, 0, 0 };
	m_MatrixTo_WOrigin = Elite::MakeTranslation(ToWorldOrigin);
	m_MatrixTo_MOrigin = Elite::MakeTranslation(ToModelOrigin);
}

void PTriangle::Reinitialize(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	m_Vertices = { v0, v1, v2 };

	Elite::FVector3 a{ m_Vertices[1].position - m_Vertices[0].position };
	Elite::FVector3 b{ m_Vertices[2].position - m_Vertices[0].position };
	m_Normal = Elite::GetNormalized(Elite::Cross(a, b));
}

void PTriangle::Update(const float elapsedSec)
{
	// The rotation matrix to apply to all the vertices
	Elite::FMatrix3 rotatingMatrix = Elite::MakeRotationY(m_RotationSpeed * elapsedSec);
	for (size_t i = 0; i < m_NmrOfVertices; ++i)
	{
		// Translate the triangle to the origin
		m_Vertices[i].position = Elite::FPoint3{ m_MatrixTo_WOrigin * Elite::FPoint4{ m_Vertices[i].position, 1.f } };
		// Rotate all the vertices of the triangle using the rotation matrix
		m_Vertices[i].position = Elite::FPoint3(rotatingMatrix * Elite::FVector3(m_Vertices[i].position));
		// Translate the triangle back to it original place
		m_Vertices[i].position = Elite::FPoint3{ m_MatrixTo_MOrigin * Elite::FPoint4{ m_Vertices[i].position, 1.f } };
	}

	// Recalculate the normal
	Elite::FVector3 a{ m_Vertices[1].position - m_Vertices[0].position };
	Elite::FVector3 b{ m_Vertices[2].position - m_Vertices[0].position };
	m_Normal = Elite::GetNormalized(Elite::Cross(a, b));
}

bool PTriangle::Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const
{
	// Create the edges that define the triangle/plane
	Elite::FVector3 a{ m_Vertices[1].position - m_Vertices[0].position };
	Elite::FVector3 b{ m_Vertices[2].position - m_Vertices[0].position };

	// Check if we intersect with our plane (yes = move on, no = stop the hit function)
	float intersectCheck{ Elite::Dot(m_Normal, ray.direction) };
	if (intersectCheck == 0)
		return false;

	// Changing cull mode check for shadows (updateHitrecord is normal hit check, !updateHitrecord is shadow check)
	if (!CheckCullMode(intersectCheck, updateHitrecord))
		return false;

	// Calculate the actual center because the z value can have different values
	auto cX{ (m_Vertices[0].position.x + m_Vertices[1].position.x + m_Vertices[2].position.x) / 3 };
	auto cY{ (m_Vertices[0].position.y + m_Vertices[1].position.y + m_Vertices[2].position.y) / 3 };
	auto cZ{ (m_Vertices[0].position.z + m_Vertices[1].position.z + m_Vertices[2].position.z) / 3 };
	Elite::FPoint3 center{ cX, cY, cZ };

	// Calculate the t value & check with the ray tMin & tMax
	Elite::FVector3 L{ center - ray.origin };
	float t{ Elite::Dot(L, m_Normal) / Elite::Dot(ray.direction, m_Normal) };
	if (t < ray.tMin || ray.tMax < t)
		return false;

	// Calculate the point where the ray hit the triangle
	Elite::FPoint3 point{ ray.origin + t * ray.direction };

	// Check if the point we calculate is inside the triangle
	// If the result of the dot-product is > 0, this means that
	// the pointToSide & the normal point in the same direction
	bool isInside1{ IsInsideTriangle(m_Vertices[1].position, m_Vertices[2].position, point, m_Normal) };
	bool isInside2{ IsInsideTriangle(m_Vertices[2].position, m_Vertices[0].position, point, m_Normal) };
	bool isInside3{ IsInsideTriangle(m_Vertices[0].position, m_Vertices[1].position, point, m_Normal) };

	if (!isInside1 || !isInside2 || !isInside3)
		return false;

	// Fill the hitrecord if this is just a normal hit check
	// Don't fill the hitrecord if it is a hitcheck for shadows
	if (updateHitrecord)
	{
		hitRecord.color = m_Color;
		hitRecord.point = point;
		hitRecord.t = t;
		hitRecord.normal = m_Normal;
	}

	return true;
}

void PTriangle::CreateVertices()
{
	Vertex v0{};
	v0.position.x = m_Origin.x - m_Width / 2;
	v0.position.y = m_Origin.y + m_Width / 2;
	v0.position.z = m_Origin.z;
	Vertex v1{};
	v1.position.x = m_Origin.x - m_Width / 2;
	v1.position.y = m_Origin.y - m_Width / 2;
	v1.position.z = m_Origin.z;
	Vertex v2{};
	v2.position.x = m_Origin.x + m_Width / 2;
	v2.position.y = m_Origin.y - m_Width / 2;
	v2.position.z = m_Origin.z;

	m_Vertices[0] = v0;
	m_Vertices[1] = v1;
	m_Vertices[2] = v2;
}
bool PTriangle::CheckCullMode(const float intersectCheck, const bool updateHitrecord) const
{
	if (updateHitrecord)
	{
		if (m_CullMode == CullMode::FRONT_FACE)
			if (intersectCheck < 0)		// Seeing front face
				return false;
		if (m_CullMode == CullMode::BACK_FACE)
			if (intersectCheck > 0)		// Seeing back face
				return false;
	}
	else
	{
		if (m_CullMode == CullMode::FRONT_FACE)
			if (intersectCheck > 0)
				return false;
		if (m_CullMode == CullMode::BACK_FACE)
			if (intersectCheck < 0)
				return false;
	}

	return true;
}