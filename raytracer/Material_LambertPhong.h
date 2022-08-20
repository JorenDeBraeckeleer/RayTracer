#pragma once
#include "Material.h"

class Material_LambertPhong final : public Material
{
public:
	Material_LambertPhong(const Elite::RGBColor& diffuseColor, const float diffuseReflectance, const float phongExponent);
	//Rule of five
	virtual ~Material_LambertPhong() = default;
	Material_LambertPhong(const Material_LambertPhong& material) = delete;
	Material_LambertPhong(Material_LambertPhong&& material) = delete;
	Material_LambertPhong& operator=(const Material_LambertPhong& material) = delete;
	Material_LambertPhong& operator=(Material_LambertPhong&& material) = delete;

	//Functions
	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override;

private:
	//Variables
	float m_SpecularReflectance;
	float m_PhongExponent;
};