#include "BRDF.h"
#include "structs.h"

Elite::RGBColor BRDF::Lambert(const Elite::RGBColor& diffuseColor, const float diffuseReflectance)
{
	return (diffuseColor * diffuseReflectance) / float(E_PI);
}

Elite::RGBColor BRDF::Phong(const float specularReflectance, const float phongExponent, const Elite::FVector3& l, const Elite::FVector3& v, const Elite::FVector3& hitNormal)
{
	Elite::FVector3 reflect = (-l + 2 * (Dot(hitNormal, l)) * hitNormal);
	float cos = Dot(reflect, v);
	float phong{ specularReflectance * powf(cos, phongExponent) };

	return Elite::RGBColor{ phong, phong, phong };
}

Elite::RGBColor BRDF::Cook_Torrance(const bool isMetal, const Elite::FVector3& viewDir, const Elite::FVector3& lightDir, const float roughness, const Elite::FVector3& hitNormal, const Elite::RGBColor& color)
{
	// Calculate half vector between view direction & light direction
	Elite::FVector3 vector = viewDir + lightDir;
	Elite::FVector3 halfVector = vector / Elite::Magnitude(vector);

	// F: Fresnel Function - How reflective are the microfacets?
	Elite::RGBColor F = CalculateFrgb(isMetal, color, halfVector, viewDir);
	// D: Normal Distribution Function - How many microfacets point in right direction?
	float D = CalculateDrgb(roughness, halfVector, hitNormal);
	// G: Geometry Function - How much shadowing and masking is happening because of the microfacets?
	float G = CalculateGrgb(roughness, viewDir, lightDir, hitNormal);
	Elite::RGBColor specular = CalculateSpecular(D, F, G, viewDir, lightDir, hitNormal);

	// Determine kd -> 1 - fresnel, cancel out if it's a metal (kd = 0)
	Elite::RGBColor kd{ (isMetal) ? Elite::RGBColor(0, 0, 0) : Elite::RGBColor(1, 1, 1) - F };
	Elite::RGBColor ks{ Elite::RGBColor(1, 1, 1) - kd };

	// Calculate Diffuse => BRDF::Lambert using the kd
	Elite::RGBColor diffuse = BRDF::Lambert(color, kd.r);

	// return finalcolor -> diffuse + specular
	return diffuse + ks * specular;
}

Elite::RGBColor BRDF::CalculateFrgb(const bool isMetal, const Elite::RGBColor& color, const Elite::FVector3& halfVector, const Elite::FVector3& viewDirection)
{
	// Determine F0 -> (0.4, 0.4, 0.4) or albedo based on metalness
	Elite::RGBColor F0{ (isMetal) ? Elite::RGBColor(color) : Elite::RGBColor(0.04f, 0.04f, 0.04f) };

	// Calculate Fresnel (F)
	Elite::RGBColor Frgb = F0 + (Elite::RGBColor(1, 1, 1) - F0) * powf((1 - Elite::Dot(halfVector, viewDirection)), 5);
	return Frgb;
}
float BRDF::CalculateDrgb(const float roughness, const Elite::FVector3& halfVector, const Elite::FVector3& hitNormal)
{
	float alpha2 = powf(roughness, 4);

	float dotNH2{ powf((Elite::Dot(hitNormal, halfVector)), 2) };

	float divisor{ float(E_PI) * ((dotNH2 * (alpha2 - 1) + 1) * (dotNH2 * (alpha2 - 1) + 1)) };
	float D = { alpha2 / divisor };

	return D;
}
float BRDF::CalculateGrgb(const float roughness, const Elite::FVector3& viewDirection, const Elite::FVector3& lightDirection, const Elite::FVector3& hitNormal)
{
	// REFERENCE: http://filmicworlds.com/blog/optimizing-ggx-shaders-with-dotlh/
	// This reference changes to dotN../.. by 1.f/..
	float alpha = powf(roughness, 2);

	float dotNV{ Elite::Clamp(Elite::Dot(hitNormal, viewDirection), 0.f, 1.f) };
	float dotNL{ Elite::Clamp(Elite::Dot(hitNormal, lightDirection), 0.f, 1.f) };
	float kDirect{ powf((alpha + 1), 2) / 8 };

	float gNVK{ dotNV / (dotNV * (1 - kDirect) + kDirect) };
	float gNLK{ dotNL / (dotNL * (1 - kDirect) + kDirect) };

	float G = { gNVK * gNLK };

	return G;
}
Elite::RGBColor BRDF::CalculateSpecular(const float d, const Elite::RGBColor& f, const float g, const Elite::FVector3& viewDIrection, const Elite::FVector3& lightDirection, const Elite::FVector3& hitNormal)
{
	float dotVN{ Elite::Dot(viewDIrection, hitNormal) };
	float dotLN{ Elite::Dot(lightDirection, hitNormal) };

	Elite::RGBColor dfg{ f * d * g };
	Elite::RGBColor specular{ dfg / 4 * (dotVN * dotLN)};
	
	return specular;
}