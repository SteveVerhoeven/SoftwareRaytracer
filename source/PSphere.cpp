#include "PSphere.h"
#include "structs.h"

PSphere::PSphere(const Elite::FPoint3& origin, const float radius, const Elite::RGBColor& color)
	   : m_Origin{ origin }
	   , m_Color{ color }
	   , m_Radius{ radius }
{}

void PSphere::Update(const float elapsedSec)
{}

bool PSphere::Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const
{
	Elite::FVector3 rts{ (ray.origin - m_Origin) };

	float a{ Elite::Dot(ray.direction, ray.direction) };
	if (a < 0) { return false; }
	float b{ 2 * Elite::Dot((ray.direction), rts) };
	//if (b == 0) { return false; }
	if (Elite::AreEqual(b, 0.f)) { return false; }
	float c{ Dot(rts, rts) - (m_Radius * m_Radius) };
	if (c < 0) { return false; }

	float discriminant{ (b * b) - (4 * a * c) };
	if (discriminant > 0)
	{
		float sqrtDiscriminant = sqrtf(discriminant);
		float t = (-b - sqrtDiscriminant) / (2.f * a);;
		if (t < ray.tMin)
			t = (-b + sqrtDiscriminant) / (2.f * a);

		if (ray.tMin < t && t < ray.tMax)
		{
			if (updateHitrecord)
			{
				hitRecord.point = ray.origin + (t * ray.direction);
				hitRecord.t = t;
				hitRecord.normal = Elite::GetNormalized(hitRecord.point - m_Origin);
				hitRecord.color = m_Color;
			}

			return true;
		}		
	}

	return false;
}