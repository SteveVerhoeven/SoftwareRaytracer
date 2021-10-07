#pragma once
#include "Material.h"

#include "BRDF.h"
#include "ERGBColor.h"

class MCookTorrance final : public Material
{
	public:
		MCookTorrance(const bool isMetal, const float roughness, const Elite::RGBColor& color);
		~MCookTorrance() = default;

		MCookTorrance(const MCookTorrance&) = delete;
		MCookTorrance(MCookTorrance&&) noexcept = delete;
		MCookTorrance& operator=(const MCookTorrance&) = delete;
		MCookTorrance& operator=(MCookTorrance&&) noexcept = delete;

		virtual void SetDiffuseColor(const Elite::RGBColor & diffuseColor) override;

	protected:
	private:
		virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override
		{ 
			return BRDF::Cook_Torrance(m_IsMetal, viewDirection, lightDirection, m_Roughness, hitRecord.normal, m_Color); 
		}

		bool m_IsMetal;
		float m_Roughness;
		Elite::RGBColor m_Color;
};

