#pragma once
#include "Material.h"

#include "BRDF.h"
#include "ERGBColor.h"

class MPhong final : public Material
{
	public:
		MPhong(const float specularReflectance, const float phongExponent);
		~MPhong() = default;

		MPhong(const MPhong&) = delete;
		MPhong(MPhong&&) noexcept = delete;
		MPhong& operator=(const MPhong&) = delete;
		MPhong& operator=(MPhong&&) noexcept = delete;
		
		virtual void SetDiffuseColor(const Elite::RGBColor& diffuseColor) override;

	protected:
	private:
		virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override
		{ return BRDF::Phong(m_SpecularReflectance, m_PhongExponent, lightDirection, viewDirection, hitRecord.normal ); }

		float m_SpecularReflectance;
		float m_PhongExponent;
};

