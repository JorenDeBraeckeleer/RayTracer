#pragma once
#include "Object.h"
#include <vector>

class Triangle;

class Mesh final : public Object
{
public:
	Mesh(const Elite::FPoint3& position, const std::vector<Elite::FPoint3>& vertexBuffer, const std::vector<int>& indexBuffer, CullMode cullMode, Material* pMaterial);
	//Rule of five
	~Mesh();
	Mesh(const Mesh& mesh) = delete;
	Mesh(Mesh&& mesh) = delete;
	Mesh& operator=(const Mesh& mesh) = delete;
	Mesh& operator=(Mesh&& mesh) = delete;

	//Functions
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) override;
	void Rotation(float elapsedTime, float totalTime, bool clockwise, bool cosineRotation) override;

private:
	//Variables
	std::vector<Elite::FPoint3> m_VertexBuffer;
	const std::vector<int> m_IndexBuffer;

	std::vector<Triangle*> m_pTriangles;

	Elite::FMatrix4 m_TranslationMatrix;
	const CullMode m_CullMode;

	Elite::FVector3 m_Normal;
};