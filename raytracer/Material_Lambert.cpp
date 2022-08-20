#include "Material_Lambert.h"

//Constructor
Material_Lambert::Material_Lambert(const Elite::RGBColor& diffuseColor, float diffuseReflectance)
	: Material(diffuseColor, diffuseReflectance)
{
}

//Calculate lambert shade color
Elite::RGBColor Material_Lambert::Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const
{
	return BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance);
}