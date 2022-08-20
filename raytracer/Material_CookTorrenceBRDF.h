#pragma once
#include "Material.h"

class Material_CookTorrenceBRDF final : public Material
{
public:
	Material_CookTorrenceBRDF(const Elite::RGBColor& albedoColor, bool metalness, float roughness);
	//Rule of five
	virtual ~Material_CookTorrenceBRDF() = default;
	Material_CookTorrenceBRDF(const Material_CookTorrenceBRDF& material) = delete;
	Material_CookTorrenceBRDF(Material_CookTorrenceBRDF&& material) = delete;
	Material_CookTorrenceBRDF& operator=(const Material_CookTorrenceBRDF& material) = delete;
	Material_CookTorrenceBRDF& operator=(Material_CookTorrenceBRDF&& material) = delete;

	//Functions
	virtual Elite::RGBColor Shade(const HitRecord & hitRecord, const Elite::FVector3 & lightDirection, const Elite::FVector3 & viewDirection) const override;

private:
	//Variables
	float m_Roughness;
	bool m_Metalness;
};