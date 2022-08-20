#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "RayHit.h"

class Material
{
public:
	Material(const Elite::RGBColor& diffuseColor, float diffuseReflectance);
	//Rule of five
	virtual ~Material() = default;
	Material(const Material& material) = delete;
	Material(Material&& material) = delete;
	Material& operator=(const Material& material) = delete;
	Material& operator=(Material&& material) = delete;

	//Functions
	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& w0lightDirection, const Elite::FVector3& viewDirection) const = 0;

protected:
	//Variables
	Elite::RGBColor m_DiffuseColor;
	float m_DiffuseReflectance;
};

//BRDF namespace
namespace BRDF
{
	//Functions
	const Elite::RGBColor Lambert(const Elite::RGBColor& diffuseColor, float diffuseReflectance);
	const Elite::RGBColor Phong(float specularReflectance, float phongExponent, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& normal);

	const float NormalDistribution(const Elite::FVector3& normal, const Elite::FVector3& halfVector, const float roughnessSquared);
	Elite::RGBColor Fresnel(const Elite::FVector3& halfVector, const Elite::FVector3& viewDirection, const Elite::RGBColor& color);
	const float Geometry(const Elite::FVector3& normal, const Elite::FVector3& viewDirection, const float k);
	const Elite::RGBColor CookTorrence(const Elite::RGBColor color, float roughness, 
		const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection, const Elite::FVector3& normal, const Elite::FVector3& halfVector, bool metalness);
}