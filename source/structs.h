#pragma once
#include "EMath.h"
#include "ERGBColor.h"

#pragma region Macros
#define DELETEPOINTER( x ) \
if (x != NULL)      \
{                   \
    delete x;       \
    x = nullptr;       \
}
#define DELETEPOINTERS( x, size ) 	\
for (size_t i{}; i < size; ++i)		\
{									\
	DELETEPOINTER(x[i]);			\
}									\
x.clear();							\

#pragma endregion

#pragma region Structs
struct Ray
{
	Elite::FPoint3 origin{};
	Elite::FVector3 direction{};
	const float tMin{ 0.0001f };
	float tMax{ FLT_MAX };
};
struct HitRecord
{
	bool isHit{};
	float t{};
	float tClosest{ FLT_MAX };
	Elite::FPoint3 point{};
	Elite::FVector3 normal{};
	Elite::RGBColor color{};
	Elite::RGBColor colorToFill{};

	void Reset() 
	{
		isHit = false;
		tClosest = FLT_MAX;
		colorToFill = { 0, 0, 0 };
	}
};

struct Screensize
{
	uint32_t width{};
	uint32_t height{};
};

struct Vertex
{
	Vertex()
	{ position = Elite::FPoint3(0, 0, 0); }
	Vertex(const float x, const float y, const float z)
	{ position = Elite::FPoint3(x, y, z); }
	Vertex(const Elite::FPoint3& pos)
	{ position = pos; }

	Elite::FPoint3 position;
};

struct RenderState
{
	RenderState()
	{
		useIrradianceOnly = false;
		useBRDFOnly = false;
		useShadows = false;
	}
	RenderState(bool irradianceOnly, bool BRDFOnly, bool shadows)
	{
		useIrradianceOnly = irradianceOnly;
		useBRDFOnly = BRDFOnly;
		useShadows = shadows;
	}

	bool useIrradianceOnly = false;
	bool useBRDFOnly = false;
	bool useShadows = true;
};

#pragma endregion