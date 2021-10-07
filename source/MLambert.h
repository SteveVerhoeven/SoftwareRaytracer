#pragma once
#include "Material.h"

#include "BRDF.h"
#include "ERGBColor.h"

class MLambert final : public Material
{
	public:
		MLambert(const float diffuseReflectance, const Elite::RGBColor& diffuseColor);
		~MLambert() = default;

		MLambert(const MLambert&) = delete;
		MLambert(MLambert&&) noexcept = delete;
		MLambert& operator=(const MLambert&) = delete;
		MLambert& operator=(MLambert&&) noexcept = delete;

		virtual void SetDiffuseColor(const Elite::RGBColor& diffuseColor) override { m_DiffuseColor = diffuseColor; };

	protected:		
	private:
		virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override
		{ return BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance); }

		float m_DiffuseReflectance;
		Elite::RGBColor m_DiffuseColor;
};

