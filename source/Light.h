#pragma once
#include "ERGBColor.h"
#include "EMath.h"

struct HitRecord;
class Light
{
	public:
		Light(const float lightIntensity, const Elite::RGBColor& lightColor);
		~Light() = default;

		Light(const Light&) = delete;
		Light(Light&&) noexcept = delete;
		Light& operator=(const Light&) = delete;
		Light& operator=(Light&&) noexcept = delete;

		virtual Elite::RGBColor CalculateIrradiance(const HitRecord& hitRecord) const = 0;

		virtual Elite::FVector3 GetDirectionShadow(const Elite::FPoint3& hitPoint) const = 0;
		virtual Elite::FVector3 GetPosition() const = 0;

		bool GetIsBurning() const { return m_IsBurning; }
		void SetIsBurning(const bool isBurning)
		{
			m_IsBurning = isBurning;
		}
	protected:
		//LightType m_LightType;
		float m_LightIntensity;
		Elite::RGBColor m_Color;
		bool m_IsBurning;
	private:
};