#include "Material_CookTorrenceBRDF.h"

//Constructor
Material_CookTorrenceBRDF::Material_CookTorrenceBRDF(const Elite::RGBColor& albedoColor, bool metalness, float roughness)
	: Material(albedoColor, {})
	, m_Roughness{roughness}
	, m_Metalness{metalness}
{
	//Roughness can't ever be 0 or lower and higher than 1
	if (m_Roughness <= 0) m_Roughness = 0.0001f;
	else if (m_Roughness > 1) m_Roughness = 1.f;
}

//Calculate BRDF cook torrance shading color
Elite::RGBColor Material_CookTorrenceBRDF::Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const
{
	//Initialze halfVector of view and light vector
	const Elite::FVector3 halfVector{ Elite::GetNormalized(viewDirection + lightDirection) };

	//If it's a plastic use the plastic color
	const Elite::RGBColor f0{ m_Metalness ? m_DiffuseColor : Elite::RGBColor{0.04f , 0.04f, 0.04f} };
	//If it's a plastic use the Fresnel function to know how much diffuse reflectance is left
	const float kdRGB{ m_Metalness ? 0.f : 1 - BRDF::Fresnel(halfVector, viewDirection, f0).g };
	
	return BRDF::Lambert(m_DiffuseColor, kdRGB) + BRDF::CookTorrence(f0, m_Roughness, lightDirection, viewDirection, hitRecord.normal, halfVector, m_Metalness);
}