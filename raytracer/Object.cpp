#include "Object.h"

//Constructor with color
Object::Object(const Elite::FPoint3& origin, const Elite::RGBColor& color)
	: m_Origin{origin}
	, m_Color{color}
	, m_pMaterial{}
{
}

//Constructor with material
Object::Object(const Elite::FPoint3& origin, Material* pMaterial)
	: m_Origin{origin}
	, m_Color{}
	, m_pMaterial{pMaterial}
{
}

//Virutal rotation function (used for triangles)
void Object::Rotation(float elapsedTime, float totalTime, bool clockwise, bool cosineRotation)
{
	return;
}

//Get material
const Material* Object::GetMaterial() const
{
	return m_pMaterial;
}