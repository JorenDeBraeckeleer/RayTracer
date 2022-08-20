#include "Material.h"

//Constructor
Material::Material(const Elite::RGBColor& diffuseColor, float diffuseReflectance)
	: m_DiffuseColor{diffuseColor}
	, m_DiffuseReflectance{diffuseReflectance}
{
}

//BRDF namespace
namespace BRDF
{
	//Calculate lambert color
	const Elite::RGBColor Lambert(const Elite::RGBColor& diffuseColor, float diffuseReflectance)
	{
		return (diffuseColor * diffuseReflectance) / (float)E_PI;
	}

	//Calculate lambert phong color
	const Elite::RGBColor Phong(float specularReflectance, float phongExponent, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& normal)
	{
		const Elite::FVector3 reflect = lightDirection - 2 * Elite::Dot(normal, lightDirection) * normal;
		const float angle = Elite::Dot(reflect, viewDirection);
		const float phongSpecularReflection = specularReflectance * pow(angle, phongExponent);
		
		return Elite::RGBColor(phongSpecularReflection, phongSpecularReflection, phongSpecularReflection);
	}

	//Calculate PBR normal distribution float
	const float NormalDistribution(const Elite::FVector3& normal, const Elite::FVector3& halfVector, const float roughnessSquared)
	{
		const float alphaSquared{ roughnessSquared * roughnessSquared };
		const float dottedVectorsSquared{ Elite::Dot(normal, halfVector) * Elite::Dot(normal, halfVector) };
		
		return alphaSquared / ((float)E_PI * (dottedVectorsSquared * (alphaSquared - 1) + 1) * (dottedVectorsSquared * (alphaSquared - 1) + 1));
	}

	//Calculate PBR Fresnel color
	Elite::RGBColor Fresnel(const Elite::FVector3& halfVector, const Elite::FVector3& viewDirection, const Elite::RGBColor& color)
	{
		const Elite::RGBColor colorMinus{ Elite::RGBColor(1.f, 1.f, 1.f) - color };
		const float dottedVectors{ Elite::Dot(halfVector, viewDirection) };
		const float dottedVectorsMinus{ 1 - dottedVectors };

		return color + colorMinus * powf(dottedVectorsMinus, 5);
	}

	//Calculate PBR Geometry float
	const float Geometry(const Elite::FVector3& normal, const Elite::FVector3& viewDirection, const float k)
	{
		const float kMinus{ 1 - k };
		const float dottedVectors{ Elite::Dot(normal, viewDirection) };

		return dottedVectors / (dottedVectors * kMinus + k);
	}

	//Calculate PBR cook torrance color
	const Elite::RGBColor CookTorrence(const Elite::RGBColor color, float roughness,
		const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& normal, const Elite::FVector3& halfVector, bool metalness)
	{
		const float roughnessSquared{ roughness * roughness };
		const float kDirectLighting{ ((roughnessSquared + 1.f) * (roughnessSquared + 1.f)) / 8.f};

		const float d{ NormalDistribution(normal, halfVector, roughnessSquared) };
		const Elite::RGBColor f{ Fresnel(halfVector, viewDirection, color) };
		const float gSmith{ Geometry(normal, viewDirection, kDirectLighting) * Geometry(normal, lightDirection, kDirectLighting) };

		return (f * d * gSmith) / (4 * Dot(viewDirection, normal) * Dot(lightDirection, normal));
	}
}