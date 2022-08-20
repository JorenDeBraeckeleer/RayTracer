#pragma once
#include "Light.h"

class DirectionalLight final : public Light
{
public:
	DirectionalLight(const Elite::FVector3& lightDirection, const Elite::RGBColor& color, float lightIntensity);
	//Rule of five
	virtual ~DirectionalLight() = default;
	DirectionalLight(const DirectionalLight& light) = delete;
	DirectionalLight(DirectionalLight&& light) = delete;
	DirectionalLight& operator=(const DirectionalLight& light) = delete;
	DirectionalLight& operator=(DirectionalLight&& light) = delete;

	//Functions
	virtual Elite::RGBColor GetIrradiance(const Elite::FPoint3& point) const override;
	virtual Elite::FVector3 GetVector(const Elite::FPoint3& point) const override;

private:
	//Variables
	const Elite::FVector3 m_LightDirection;
};

