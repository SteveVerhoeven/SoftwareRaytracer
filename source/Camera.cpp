#include "Camera.h"
#include "EMath.h"

Camera::Camera(const Elite::FPoint3& position, const float angleDegrees)
	  : m_AngleRadians{ angleDegrees * (float)E_TO_RADIANS }
	  , m_FOV{}
	  , m_AspectRatio{}
	  , m_Screensize{}
	  , m_Position{ position }
	  , m_Forward{0, 0, 1}
	  , m_Right{1, 0, 0}
	  , m_Up{0, 1, 0}
	  , m_WorldUp{0, 1, 0}
	  , m_ONB{ m_ONB.Identity() }
{}
Camera::~Camera()
{}
void Camera::Initialize(const uint32_t& screenWidth, const uint32_t& screenHeight)
{
	m_Screensize.width = screenWidth;
	m_Screensize.height = screenHeight;

	m_AspectRatio = (float)screenWidth / screenHeight;
	m_FOV = tan(m_AngleRadians / 2);

	CreateONB();
}
void Camera::Update(const float elapsedSec)
{}

void Camera::ConstructRay(Ray& ray, const uint32_t& x, const uint32_t& y)
{
	float xSS{ (2 * ((x + 0.5f) / m_Screensize.width) - 1) * m_AspectRatio * m_FOV };
	float ySS{ (1 - 2 * ((y + 0.5f) / m_Screensize.height)) * m_FOV };
	float zSS{ -1.f };

	Elite::FPoint3 samplePos{ xSS, ySS, zSS };
	Elite::FPoint4 transformedPos{ m_ONB * Elite::FPoint4(samplePos, 1.f) };
	Elite::FVector4 dir4{ (transformedPos - Elite::FPoint4(m_Position, 1)) };

	// Assemble the ray struct
	ray.origin = m_Position;
	ray.direction = Elite::FVector3(GetNormalized(dir4));
}
void Camera::MoveForward(const float z, const float y)
{
	Elite::FMatrix3 RotationMatrixY{ MakeRotation(y / 250, m_WorldUp) };		// Move around Y-axis	
	m_Forward = Elite::GetNormalized(RotationMatrixY * m_Forward);
	
	Elite::FMatrix4 TranslationMatrix{ MakeTranslation(m_Forward * -z) };
	m_Position = Elite::FPoint3{ TranslationMatrix * Elite::FPoint4{ m_Position, 1 } };
	
	CreateONB();
}
void Camera::MoveUp(const float x)
{
	Elite::FMatrix4 TranslationMatrix{ MakeTranslation((m_Up)*x) };
	m_Position = Elite::FPoint3{ TranslationMatrix * Elite::FPoint4{ m_Position, 1 } };

	CreateONB();
}
void Camera::MoveRotation(const float y, const float x)
{
	Elite::FMatrix3 RotationMatrixY{ MakeRotation(y, m_Up) };
	Elite::FMatrix3 RotationMatrixX{ MakeRotation(x, m_Right) };
	m_Forward = Elite::GetNormalized(RotationMatrixY * RotationMatrixX * m_Forward);

	CreateONB();
}

void Camera::CreateONB()
{
	m_Right = GetNormalized(Cross(m_WorldUp, m_Forward));
	m_Up = GetNormalized(Cross(m_Forward, m_Right));

	m_ONB = { m_Right, m_Up, m_Forward, Elite::FVector4(Elite::FVector3(m_Position), 1.f) };
}