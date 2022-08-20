#pragma once
#include "Object.h"

class Triangle final : public Object
{
public:
	Triangle(const Elite::FPoint3& position, const Elite::FPoint3& vertex0, const Elite::FPoint3& vertex1, const Elite::FPoint3& vertex2, CullMode cullMode, Material* pMaterial);
	//Rule of five
	virtual ~Triangle() = default;
	Triangle(const Triangle& triangle) = delete;
	Triangle(Triangle&& triangle) = delete;
	Triangle& operator=(const Triangle& triangle) = delete;
	Triangle& operator=(Triangle&& triangle) = delete;

	//Functions
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) override;
	virtual void Rotation(float elapsedTime, float totalTime, bool clockwise, bool cosineRotation) override;

private:
	//Variables
	Elite::FPoint4 m_Vertex0;
	Elite::FPoint4 m_Vertex1;
	Elite::FPoint4 m_Vertex2;

	Elite::FMatrix4 m_PositionMatrix;
	Elite::FVector3 m_Normal;
	CullMode m_CullMode;
};
