#pragma once
#include "Light.h"

class LDirectional final : public Light
{
	public:
		LDirectional(const float lightIntensity, const Elite::RGBColor& lightColor, const Elite::FVector3& direction);
		~LDirectional() = default;

		LDirectional(const LDirectional&) = delete;
		LDirectional(LDirectional&&) noexcept = delete;
		LDirectional& operator=(const LDirectional&) = delete;
		LDirectional& operator=(LDirectional&&) noexcept = delete;

		virtual Elite::RGBColor CalculateIrradiance(const HitRecord& hitRecord) const override;

		virtual Elite::FVector3 GetDirectionShadow(const Elite::FPoint3& hitPoint) const override;
		virtual Elite::FVector3 GetPosition() const override { return m_Direction; };

	private:
		Elite::FVector3 m_Direction;
};