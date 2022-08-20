#include "Mesh.h"
#include "Triangle.h"
#include "Material.h"
#include "Material_CookTorrenceBRDF.h"

//Constructor
Mesh::Mesh(const Elite::FPoint3& position, const std::vector<Elite::FPoint3>& vertexBuffer, const std::vector<int>& indexBuffer, CullMode cullMode, Material* pMaterial)
	: Object(position, pMaterial)
	, m_VertexBuffer{vertexBuffer}
	, m_IndexBuffer{indexBuffer}
	, m_TranslationMatrix{m_TranslationMatrix.Identity()}
	, m_CullMode{cullMode}
	, m_Normal{}
{
	//Initialze buffer size
	const int vertexBufferSize = (int)vertexBuffer.size();

	//Loop over vertices
	//Add vertices to the origin
	//Calculate center of the vertices by dividing by the amount of vertices
	for (const Elite::FPoint3& vertices : vertexBuffer)
	{
		m_Origin.x += vertices.x;
		m_Origin.y += vertices.y;
		m_Origin.z += vertices.z;
	}
	m_Origin.x /= vertexBufferSize;
	m_Origin.y /= vertexBufferSize;
	m_Origin.z /= vertexBufferSize;

	//Calculate translationmatrix with the new origin/center
	m_TranslationMatrix.data[3][0] = m_Origin.x;
	m_TranslationMatrix.data[3][1] = m_Origin.y;
	m_TranslationMatrix.data[3][2] = m_Origin.z;

	//Calculate origin with new positionmatrix
	m_Origin = (m_TranslationMatrix * Elite::FPoint4(m_Origin)).xyz;

	for (int i = 0; i < (int)m_IndexBuffer.size(); i += 3)
	{
		//Pull the vertex values with the indices
		const Elite::FPoint3 vertex0 = m_VertexBuffer[m_IndexBuffer[i + size_t(0)]];
		const Elite::FPoint3 vertex1 = m_VertexBuffer[m_IndexBuffer[i + size_t(1)]];
		const Elite::FPoint3 vertex2 = m_VertexBuffer[m_IndexBuffer[i + size_t(2)]];

		m_pTriangles.push_back(new Triangle{ m_Origin, vertex0, vertex1, vertex2, m_CullMode, m_pMaterial });

		//https://github.com/smokindinesh/Modern-OpenGL-Series/blob/master/9_OBJLoader/src/Mesh.cpp
	}
}

Mesh::~Mesh()
{
	for (Triangle* pTriangle : m_pTriangles)
	{
		delete pTriangle;
		pTriangle = nullptr;
	}
}

//Pure virtual function to check if the ray has a hit
bool Mesh::Hit(const Ray& ray, HitRecord& hitRecord)
{
	//Initialize bool
	bool hit{};

	//Loop over all triangles
	for (Triangle* pTriangle : m_pTriangles)
	{
		if (pTriangle->Hit(ray, hitRecord))
		{
			//If there is a hit set the bool true
			hit = true;
		}
	}
	return hit;
}

//Virtual function to rotate the mesh
void Mesh::Rotation(float elapsedTime, float totalTime, bool clockwise, bool cosineRotation)
{
	//Loop over all triangles
	for (Triangle* pTriangle : m_pTriangles)
	{
		//Rotate triangles
		pTriangle->Rotation(elapsedTime, totalTime, clockwise, false);
	}
}