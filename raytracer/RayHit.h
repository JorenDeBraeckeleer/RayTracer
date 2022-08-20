#pragma once
#include "EMath.h"
#include "ERGBColor.h"

struct Ray
{
public:
	//Constructor with default values
	Ray(const Elite::FPoint3& origin = {}, const Elite::FVector3& direction = {}, const float tMin = 0.0001f, const float tMax = FLT_MAX)
		: origin{origin}
		, direction{direction}
		, tMin{tMin}
		, tMax{tMax}
	{
	}

	//Constructor with specific tMax for lights
	Ray(Elite::FPoint3& origin, const Elite::FVector3& direction, const float tMax)
		: origin{ origin }
		, direction{ direction }
		, tMin{0.0001f}
		, tMax{ tMax }
	{
	}

	//Variables
	Elite::FPoint3 origin;
	Elite::FVector3 direction;
	const float tMin;
	const float tMax;
};

struct HitRecord
{
public:
	//Constructor
	HitRecord(const Elite::FVector3& hitPoint = {}, const Elite::FVector3& normal = {}, const Elite::RGBColor& color = {}, float tValue = FLT_MAX)
		: hitPoint{hitPoint}
		, normal{normal}
		, color{color}
		, tValue{tValue}
	{
	}

	//Variables
	Elite::FPoint3 hitPoint;
	Elite::FVector3 normal;
	Elite::RGBColor color;
	float tValue;
};