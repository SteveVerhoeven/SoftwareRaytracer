#pragma once
#include "EMath.h"
#include "ERGBColor.h"

struct Ray;
struct HitRecord;
struct Vertex;
class Primitive
{
	public:
		enum class CullMode
		{
			NO_CULLING = 0,
			FRONT_FACE = 1,
			BACK_FACE = 2
		};

		Primitive() = default;
		virtual ~Primitive() = default;

		Primitive(const Primitive&) = delete;
		Primitive(Primitive&&) noexcept = delete;
		Primitive& operator=(const Primitive&) = delete;
		Primitive& operator=(Primitive&&) noexcept = delete;

		virtual void Update(const float elapsedSec) = 0;
		virtual bool Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const = 0;
	private:
};