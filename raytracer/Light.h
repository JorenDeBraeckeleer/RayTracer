#pragma once
#include "EMath.h"
#include "ERGBColor.h"

class Light
{
public:
	Light(const Elite::RGBColor& color, float lightIntensity);
	//Rule of five
	virtual ~Light() = default;
	Light(const Light& light) = delete;
	Light(Light&& light) = delete;
	Light& operator=(const Light& light) = delete;
	Light& operator=(Light&& light) = delete;

	//Functions
	virtual Elite::RGBColor GetIrradiance(const Elite::FPoint3& point) const = 0;
	virtual Elite::FVector3 GetVector(const Elite::FPoint3& point) const = 0;

protected:
	//Variables
	const Elite::RGBColor m_Color;
	const float m_LightIntensity;
};