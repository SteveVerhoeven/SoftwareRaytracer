#pragma once
#include "Primitive.h"

class PSphere final : public Primitive
{
	public:
		PSphere(const Elite::FPoint3& origin, const float radius, const Elite::RGBColor& color = {});
		virtual ~PSphere() = default;

		PSphere(const PSphere&) = delete;
		PSphere(PSphere&&) noexcept = delete;
		PSphere& operator=(const PSphere&) = delete;
		PSphere& operator=(PSphere&&) noexcept = delete;

		virtual void Update(const float elapsedSec) override;
		virtual bool Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const override;
	private:
		Elite::FPoint3 m_Origin;
		Elite::RGBColor m_Color;
		float m_Radius;
};