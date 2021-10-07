#include "PPlane.h"
#include "structs.h"

PPlane::PPlane(const Elite::FPoint3& position, const Elite::FVector3& direction, const Elite::RGBColor& color)
	  : m_Position{ position }
	  , m_Direction{ direction }
	  , m_Color{ color }
{}

void PPlane::Update(const float elapsedSec)
{
}

bool PPlane::Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const
{
	const float upperFraction{ Dot((m_Position - ray.origin), m_Direction) };
	const float lowerFraction{ Dot(ray.direction, m_Direction) };

	const float t{ upperFraction / lowerFraction };
	if ((ray.tMin < t) && (t < ray.tMax))
	{
		if (updateHitrecord)
		{
			hitRecord.t = t;
			hitRecord.point = ray.origin + (t * ray.direction);
			hitRecord.normal = m_Direction;
			hitRecord.color = m_Color;
		}

		return true;
	}

	return false;
}