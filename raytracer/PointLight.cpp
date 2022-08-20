#include "PointLight.h"

//Constructor
PointLight::PointLight(const Elite::FPoint3& lightPosition, const Elite::RGBColor& color, float lightIntensity)
	: Light(color, lightIntensity)
	, m_LightPosition{lightPosition}
{
}

//Calculate irradiance color
Elite::RGBColor PointLight::GetIrradiance(const Elite::FPoint3& point) const
{
	return m_Color * m_LightIntensity / Elite::SqrMagnitude(m_LightPosition - point);
}

//Get light vector
Elite::FVector3 PointLight::GetVector(const Elite::FPoint3& point) const
{
	return m_LightPosition - point;
}