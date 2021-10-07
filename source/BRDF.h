#pragma once
#include "ERGBColor.h"
#include "EMath.h"

struct HitRecord;
class BRDF final
{
	public:
		BRDF() = default;
		~BRDF() = default;

		BRDF(const BRDF&) = delete;
		BRDF(BRDF&&) noexcept = delete;
		BRDF& operator=(const BRDF&) = delete;
		BRDF& operator=(BRDF&&) noexcept = delete;

		static Elite::RGBColor Lambert(const Elite::RGBColor& diffuseColor, const float diffuseReflectance);
		static Elite::RGBColor Phong(const float specularReflectance, const float phongExponent, const Elite::FVector3& l, const Elite::FVector3& v, const Elite::FVector3& hitNormal);
		static Elite::RGBColor Cook_Torrance(const bool isMetal, const Elite::FVector3& viewDir, const Elite::FVector3& lightDir, const float roughness, const Elite::FVector3& hitNormal, const Elite::RGBColor& color);

	private:
		static Elite::RGBColor CalculateFrgb(const bool isMetal, const Elite::RGBColor& color, const Elite::FVector3& halfVector, const Elite::FVector3& viewDirection);
		static float CalculateDrgb(const float roughness, const Elite::FVector3& halfVector, const Elite::FVector3& hitNormal);
		static float CalculateGrgb(const float roughness, const Elite::FVector3& halfVector, const Elite::FVector3& lightDirection, const Elite::FVector3& hitNormal);
		static Elite::RGBColor CalculateSpecular(const float d, const Elite::RGBColor& f, const float g, const Elite::FVector3& viewDIrection, const Elite::FVector3& lightDirection, const Elite::FVector3& hitNormal);
};

