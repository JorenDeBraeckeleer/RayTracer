#pragma once
#include "Object.h"

class Plane final : public Object
{
public:
	Plane(const Elite::FPoint3& planeOrigin, const Elite::FVector3& planeNormal, const Elite::RGBColor& color);
	Plane(const Elite::FPoint3& planeOrigin, const Elite::FVector3& planeNormal, Material* pMaterial);
	//Rule of five
	virtual ~Plane() = default;
	Plane(const Plane& plane) = delete;
	Plane(Plane&& plane) = delete;
	Plane& operator=(const Plane& plane) = delete;
	Plane& operator=(Plane&& plane) = delete;

	//Functions
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) override;

private:
	//Variables
	const Elite::FVector3 m_Normal;
};