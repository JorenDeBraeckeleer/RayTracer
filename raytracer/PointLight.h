#pragma once
#include "Light.h"

class PointLight final : public Light
{
public:
	PointLight(const Elite::FPoint3& lightPosition, const Elite::RGBColor& color, float lightIntensity);
	//Rule of five
	virtual ~PointLight() = default;
	PointLight(const PointLight& light) = delete;
	PointLight(PointLight&& light) = delete;
	PointLight& operator=(const PointLight& light) = delete;
	PointLight& operator=(PointLight&& light) = delete;

	//Functions
	virtual Elite::RGBColor GetIrradiance(const Elite::FPoint3& point) const override;
	virtual Elite::FVector3 GetVector(const Elite::FPoint3& point) const override;

private:
	//Variables
	const Elite::FPoint3 m_LightPosition;
};

