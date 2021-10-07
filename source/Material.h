#pragma once
#include "ERGBColor.h"
#include "structs.h"

class Material
{
	public:
		Material() = default;
		~Material() = default;

		Material(const Material&) = delete;
		Material(Material&&) noexcept = delete;
		Material& operator=(const Material&) = delete;
		Material& operator=(Material&&) noexcept = delete;

		virtual void SetDiffuseColor(const Elite::RGBColor& diffuseColor) = 0;
		virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const = 0;
	protected:
	private:
};