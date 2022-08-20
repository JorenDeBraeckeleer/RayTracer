#pragma once
#include "EMath.h"
#include "ERGBColor.h"
#include "RayHit.h"
#include "Material.h"

class Object
{
public:
	Object(const Elite::FPoint3& origin, const Elite::RGBColor& color);
	Object(const Elite::FPoint3& origin, Material* pMaterial);
	//Rule of five
	virtual ~Object() = default;
	Object(const Object& object) = delete;
	Object(Object&& object) = delete;
	Object& operator=(const Object& object) = delete;
	Object& operator=(Object&& object) = delete;

	//Functions
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) = 0;
	virtual void Rotation(float elapsedTime, float totalTime, bool clockwise, bool cosineRotation);

	const Material* GetMaterial() const;

protected:
	//Variables
	Elite::FPoint3 m_Origin;
	const Elite::RGBColor m_Color;
	Material* m_pMaterial;
};

//Enum class for cull modes (used for triangles)
enum class CullMode
{
	BackFaceCulling,	//Back face cut out
	FrontFaceCulling,	//Front face cut out
	NoCulling			//No faces cut out
};