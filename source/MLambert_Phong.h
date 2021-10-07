#pragma once
#include "Material.h"

#include "BRDF.h"
#include "ERGBColor.h"

class MLambert_Phong final : public Material
{
	public:
		MLambert_Phong(const float diffuseReflectance, const Elite::RGBColor& diffuseColor, const float specularReflectance, const float phongExponent);
		~MLambert_Phong() = default;

		MLambert_Phong(const MLambert_Phong&) = delete;
		MLambert_Phong(MLambert_Phong&&) noexcept = delete;
		MLambert_Phong& operator=(const MLambert_Phong&) = delete;
		MLambert_Phong& operator=(MLambert_Phong&&) noexcept = delete;

		virtual void SetDiffuseColor(const Elite::RGBColor & diffuseColor) override { m_DiffuseColor = diffuseColor; };

	protected:
	private:
		virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override
		{
			return BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance) +
				   BRDF::Phong(m_SpecularReflectance, m_PhongExponent, lightDirection, viewDirection, hitRecord.normal);
		}
		float m_SpecularReflectance;
		float m_PhongExponent;
		float m_DiffuseReflectance;
		Elite::RGBColor m_DiffuseColor;
};

