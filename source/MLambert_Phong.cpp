#include "MLambert_Phong.h"

MLambert_Phong::MLambert_Phong(const float diffuseReflectance, const Elite::RGBColor& diffuseColor, const float specularReflectance, const float phongExponent)
			  : m_DiffuseReflectance{ diffuseReflectance }
			  , m_DiffuseColor{ diffuseColor }
			  , m_SpecularReflectance{ specularReflectance }
			  , m_PhongExponent{ phongExponent }
{
}
