#include "MLambert.h"

MLambert::MLambert(const float diffuseReflectance, const Elite::RGBColor& diffuseColor)
	    : m_DiffuseColor{ diffuseColor }
	    , m_DiffuseReflectance{ diffuseReflectance }
{
}
