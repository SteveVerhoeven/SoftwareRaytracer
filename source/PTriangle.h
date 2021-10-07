#pragma once
#include "Primitive.h"
#include <vector>

class PTriangle final : public Primitive
{
	public:
		PTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const CullMode& cullMode, const Elite::RGBColor& color = {});
		PTriangle(const Elite::FPoint3& origin, const float width, const CullMode& cullMode, const Elite::RGBColor& color = {});
		virtual ~PTriangle() = default;

		PTriangle(const PTriangle&) = delete;
		PTriangle(PTriangle&&) noexcept = delete;
		PTriangle& operator=(const PTriangle&) = delete;
		PTriangle& operator=(PTriangle&&) noexcept = delete;

		void Reinitialize(const Vertex& v0, const Vertex& v1, const Vertex& v2);
		virtual void Update(const float elapsedSec) override;
		virtual bool Hit(const Ray& ray, HitRecord& hitRecord, const bool updateHitrecord) const override;

	private:
		int m_NmrOfVertices;
		float m_Width;
		float m_RotationSpeed;
		CullMode m_CullMode;
		Elite::FPoint3 m_Origin;
		Elite::RGBColor m_Color;
		Elite::FVector3 m_Normal;
		Elite::FMatrix4 m_MatrixTo_WOrigin;
		Elite::FMatrix4 m_MatrixTo_MOrigin;
		std::vector<Vertex> m_Vertices;

		bool IsInsideTriangle(const Elite::FPoint3& a, const Elite::FPoint3& b, const Elite::FPoint3& p, const Elite::FVector3& n) const
		{
			Elite::FVector3 c{ Elite::Cross(p - a, b - a) };
			float directionCheck{ Elite::Dot(n, c) };

			return directionCheck < 0;
		}

		void CreateVertices();		
		bool CheckCullMode(const float intersectCheck, const bool updateHitrecord) const;
};