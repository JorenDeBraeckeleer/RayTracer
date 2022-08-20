#pragma once
#include "Object.h"

class Sphere final : public Object
{
public:
	Sphere(const Elite::FPoint3& sphereOrigin, const float sphereRadius, const Elite::RGBColor& color);
	Sphere(const Elite::FPoint3& sphereOrigin, const float sphereRadius, Material* pMaterial);
	//Rule of five
	virtual ~Sphere() = default;
	Sphere(const Sphere& sphere) = delete;
	Sphere(Sphere&& sphere) = delete;
	Sphere& operator=(const Sphere& sphere) = delete;
	Sphere& operator=(Sphere&& sphere) = delete;

	//Functions
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) override;

private:
	//Variables
	const float m_Radius;
};