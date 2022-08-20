#include "Sphere.h"

//Constructor with color
Sphere::Sphere(const Elite::FPoint3& sphereOrigin, const float sphereRadius, const Elite::RGBColor& color)
	: Object(sphereOrigin, color)
	, m_Radius{sphereRadius}
{
}

//Constructor with material
Sphere::Sphere(const Elite::FPoint3& sphereOrigin, const float sphereRadius, Material* pMaterial)
	: Object(sphereOrigin, pMaterial)
	, m_Radius{sphereRadius}
{
}

//Pure virtual function to check if the ray has a hit
bool Sphere::Hit(const Ray& ray, HitRecord& hitRecord)
{
	//Initialize variables for the discriminant
	const float a{ Dot(ray.direction, ray.direction) };
	const float b{ Dot(2 * ray.direction, ray.origin - m_Origin) };
	const float c{ Dot(ray.origin - m_Origin, ray.origin - m_Origin) - m_Radius * m_Radius };

	const float discriminant{ b * b - 4 * a * c };

	//Initialze tValue
	float tValue{ (-b - sqrt(discriminant)) / (2 * a) };
	//Change tValue if you are inside of a sphere
	if (tValue < ray.tMin) tValue = (-b + sqrt(discriminant)) / (2 * a); //To find the projected point of the intersection
	
	//If the discriminant is zero or lower it has none or exactly 1 intersection
	if (discriminant <= 0) return false;

	//If tValue is between the tValues of the ray and smaller than the tValue of the hitrecord
	if (tValue > ray.tMin && tValue < ray.tMax && tValue < hitRecord.tValue)
	{
		//Copy all variables into the hitrecord
		hitRecord.hitPoint = ray.origin + tValue * ray.direction;
		hitRecord.normal = (hitRecord.hitPoint - m_Origin) / m_Radius;
		hitRecord.tValue = tValue;
		hitRecord.color = m_Color;

		//Return a hit
		return true;
	}
	//return no hit
	return false;
}