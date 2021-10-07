#pragma once
#include "Light.h"

class LPoint final : public Light
{
	public:
		LPoint(const float lightIntensity, const Elite::RGBColor& lightColor, const Elite::FVector3& position);
		~LPoint() = default;

		LPoint(const LPoint&) = delete;
		LPoint(LPoint&&) noexcept = delete;
		LPoint& operator=(const LPoint&) = delete;
		LPoint& operator=(LPoint&&) noexcept = delete;

		virtual Elite::RGBColor CalculateIrradiance(const HitRecord& hitRecord) const;
		
		virtual Elite::FVector3 GetDirectionShadow(const Elite::FPoint3& hitPoint) const override;
		virtual Elite::FVector3 GetPosition() const override { return m_Position; };

	private:
		Elite::FVector3 m_Position;
};