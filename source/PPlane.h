#pragma once
#include "Primitive.h"

class PPlane final : public Primitive
{
	public:
		PPlane(const Elite::FPoint3& position, const Elite::FVector3& direction, const Elite::RGBColor& color = {});
		virtual ~PPlane() = default;

		PPlane(const PPlane&) = delete;
		PPlane(PPlane&&) noexcept = delete;
		PPlane& operator=(const PPlane&) = delete;
		PPlane& operator=(PPlane&&) noexcept = delete;

		virtual void Update(const float elapsedSec) override;
		virtual bool Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const override;
	private:
		Elite::FPoint3 m_Position;
		Elite::FVector3 m_Direction;
		Elite::RGBColor m_Color;
};