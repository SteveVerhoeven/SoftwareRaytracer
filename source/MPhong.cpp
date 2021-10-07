#include "MPhong.h"

MPhong::MPhong(const float specularReflectance, const float phongExponent)
	  : m_SpecularReflectance{ specularReflectance }
	  , m_PhongExponent{ phongExponent }
{}

void MPhong::SetDiffuseColor(const Elite::RGBColor& diffuseColor)
{
}
