#pragma once
#include "structs.h"

class Camera final
{
	public:
		Camera(const Elite::FPoint3& position, const float angleDegrees);
		~Camera();

		Camera(const Camera&) = delete;
		Camera(Camera&&) noexcept = delete;
		Camera& operator=(const Camera&) = delete;
		Camera& operator=(Camera&&) noexcept = delete;

		void Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight);
		void Update(const float elapsedSec);

		void ConstructRay(Ray& ray, const uint32_t& x, const uint32_t& y);

		void MoveForward(const float z, const float y);
		void MoveUp(const float x);
		void MoveRotation(const float y, const float x);

	private:
		float m_AngleRadians;
		float m_FOV;
		float m_AspectRatio;
		Screensize m_Screensize;
		Elite::FPoint3 m_Position;
		Elite::FVector3 m_Forward;
		Elite::FVector3 m_Right;
		Elite::FVector3 m_Up;
		Elite::FVector3 m_WorldUp;
		Elite::FMatrix4 m_ONB;

		void CreateONB();
};