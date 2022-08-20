#include "Material_LambertPhong.h"

//Constructor
Material_LambertPhong::Material_LambertPhong(const Elite::RGBColor& diffuseColor, const float diffuseReflectance, const float phongExponent)
	: Material(diffuseColor, diffuseReflectance)
	, m_SpecularReflectance{1 - diffuseReflectance}
	, m_PhongExponent{phongExponent}
{
}

//Calculate lambert phong shading color
Elite::RGBColor Material_LambertPhong::Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const
{
	return BRDF::Lambert(m_DiffuseColor, m_DiffuseReflectance) + BRDF::Phong(m_SpecularReflectance, m_PhongExponent, lightDirection, viewDirection, hitRecord.normal);
}