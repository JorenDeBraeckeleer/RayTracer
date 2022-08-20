#include "DirectionalLight.h"

//Constructor
DirectionalLight::DirectionalLight(const Elite::FVector3& lightDirection, const Elite::RGBColor& color, float lightIntensity)
	: Light(color, lightIntensity)
	, m_LightDirection{lightDirection}
{
}

//Calculate irradiance color
Elite::RGBColor DirectionalLight::GetIrradiance(const Elite::FPoint3& point) const
{
	return m_Color * m_LightIntensity;
}

//Get light vector
Elite::FVector3 DirectionalLight::GetVector(const Elite::FPoint3& point) const
{
	return m_LightDirection;
}