#include "Light.h"

//Constructor
Light::Light(const Elite::RGBColor& color, float lightIntensity)
	: m_Color{color}
	, m_LightIntensity{lightIntensity}
{
}