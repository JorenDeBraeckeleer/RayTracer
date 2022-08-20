#include "Plane.h"

//Constructor with color
Plane::Plane(const Elite::FPoint3& planeOrigin, const Elite::FVector3& planeNormal, const Elite::RGBColor& color)
	: Object(planeOrigin, color)
	, m_Normal{planeNormal}
{
}

//Constructor with material
Plane::Plane(const Elite::FPoint3& planeOrigin, const Elite::FVector3& planeNormal, Material* pMaterial)
	: Object(planeOrigin, pMaterial)
	, m_Normal{planeNormal}
{
}

//Pure virtual function to check if the ray has a hit
bool Plane::Hit(const Ray& ray, HitRecord& hitRecord)
{
	//Initialze tValue
	float tValue{ Elite::Dot((m_Origin - ray.origin), m_Normal) / Elite::Dot(ray.direction, m_Normal) };

	//If tValue is between the tValues of the ray and smaller than the tValue of the hitrecord
	if (tValue > ray.tMin && tValue < ray.tMax && tValue < hitRecord.tValue)
	{
		//Copy all variables into the hitrecord
		hitRecord.hitPoint = ray.origin + tValue * ray.direction;
		hitRecord.normal = m_Normal;
		hitRecord.tValue = tValue;
		hitRecord.color= m_Color;

		//Return a hit
		return true;
	}
	//Return no hit
	else return false;
}