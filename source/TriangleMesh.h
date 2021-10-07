#pragma once
#include "Primitive.h"

#include "structs.h"
#include <vector>

class PTriangle;
class TriangleMesh final : public Primitive
{
	public:
		TriangleMesh(const CullMode& cullMode, const Elite::RGBColor& color);
		virtual ~TriangleMesh() = default;

		TriangleMesh(const TriangleMesh&) = delete;
		TriangleMesh(TriangleMesh&&) noexcept = delete;
		TriangleMesh& operator=(const TriangleMesh&) = delete;
		TriangleMesh& operator=(TriangleMesh&&) noexcept = delete;

		void Initialize();
		virtual void Update(const float elapsedSec) override;
		virtual bool Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const override;

	protected:
	private:
		CullMode m_CullMode;
		Elite::RGBColor m_Color;

		std::vector<Vertex> m_VertexBuffer;
		std::vector<size_t> m_IndexBuffer;
		std::vector<PTriangle*> m_Triangles;
};