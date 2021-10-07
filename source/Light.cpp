#include "Light.h"

Light::Light(const float lightIntensity, const Elite::RGBColor& lightColor)
	 : m_LightIntensity{lightIntensity}
	 , m_Color{lightColor}
	 , m_IsBurning{true}
{}