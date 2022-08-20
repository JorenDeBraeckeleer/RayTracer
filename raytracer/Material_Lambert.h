#pragma once
#include "Material.h"

class Material_Lambert final : public Material
{
public:
	Material_Lambert(const Elite::RGBColor& diffuseColor, float diffuseReflectance);
	//Rule of five
	virtual ~Material_Lambert() = default;
	Material_Lambert(const Material_Lambert& material) = delete;
	Material_Lambert(Material_Lambert&& material) = delete;
	Material_Lambert& operator=(const Material_Lambert& material) = delete;
	Material_Lambert& operator=(Material_Lambert&& material) = delete;

	//Functions
	virtual Elite::RGBColor Shade(const HitRecord& hitRecord, const Elite::FVector3& lightDirection, const Elite::FVector3& viewDirection) const override;
};

