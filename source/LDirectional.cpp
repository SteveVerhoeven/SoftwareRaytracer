#include "LDirectional.h"
#include "EPoint.h"
#include "EMath.h"

#include "structs.h"

LDirectional::LDirectional(const float lightIntensity, const Elite::RGBColor& lightColor, const Elite::FVector3& direction)
	: Light(lightIntensity, lightColor)
	, m_Direction{ direction }
{}

Elite::RGBColor LDirectional::CalculateIrradiance(const HitRecord& hitRecord) const
{
	Elite::RGBColor Ergb{};

	// If it is not burning return no light
	if (!m_IsBurning)
		return Ergb;

	// Else calculate the Irradiance	
	float cosineLaw{ Dot(hitRecord.normal, GetNormalized(m_Direction)) };

	if (cosineLaw < 0)
	{
		return Ergb;
	}

	Ergb = m_Color * m_LightIntensity * cosineLaw;
	return Ergb;
}

Elite::FVector3 LDirectional::GetDirectionShadow(const Elite::FPoint3& hitPoint) const
{
	return m_Direction;
}
