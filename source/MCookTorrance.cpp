#include "MCookTorrance.h"

MCookTorrance::MCookTorrance(const bool metalness, const float roughness, const Elite::RGBColor& albedo)
	         : m_IsMetal{metalness}
	         , m_Roughness{roughness}
	         , m_Color{albedo}
{}

void MCookTorrance::SetDiffuseColor(const Elite::RGBColor& diffuseColor)
{
}
