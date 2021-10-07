#include "LPoint.h"
#include "structs.h"

LPoint::LPoint(const float lightIntensity, const Elite::RGBColor& lightColor, const Elite::FVector3& position)
	: Light(lightIntensity, lightColor)
	, m_Position{ position }
{}

Elite::RGBColor LPoint::CalculateIrradiance(const HitRecord& hitRecord) const
{
	Elite::RGBColor Ergb{};
	
	// If it is not burning return no light
	if (!m_IsBurning)
		return Ergb;

	// Else calculate the Irradiance
	Elite::FVector3 direction{ m_Position - Elite::FVector3{ hitRecord.point } };
	float cosineLaw{ Dot(hitRecord.normal, GetNormalized(direction)) };

	if (cosineLaw < 0)
		return Ergb;

	Ergb = m_Color * (m_LightIntensity / SqrMagnitude(direction));

	return (Ergb * cosineLaw);
}

Elite::FVector3 LPoint::GetDirectionShadow(const Elite::FPoint3& hitPoint) const
{
	return (Elite::FPoint3(m_Position) - hitPoint);
}