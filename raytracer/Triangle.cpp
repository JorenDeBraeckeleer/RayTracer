#include "Triangle.h"

//Constructor
Triangle::Triangle(const Elite::FPoint3& position, const Elite::FPoint3& vertex0, const Elite::FPoint3& vertex1, const Elite::FPoint3& vertex2, CullMode cullMode, Material* pMaterial)
	: Object(Elite::FPoint3((vertex0.x + vertex1.x + vertex2.x) / 3,
							(vertex0.y + vertex1.y + vertex2.y) / 3,
							(vertex0.z + vertex1.z + vertex2.z) / 3), pMaterial)
	, m_Vertex0{vertex0}
	, m_Vertex1{vertex1}
	, m_Vertex2{vertex2}
	, m_PositionMatrix{m_PositionMatrix.Identity()}
	, m_CullMode{cullMode}
	, m_Normal{Elite::GetNormalized(Elite::Cross((vertex1 - vertex0), (vertex2 - vertex0)))}
{
	//Put position in the positionmatrix
	m_PositionMatrix.data[3][0] = position.x;
	m_PositionMatrix.data[3][1] = position.y;
	m_PositionMatrix.data[3][2] = position.z;

	//Calculate vertices with new positionmatrix
	m_Vertex0 = m_PositionMatrix * m_Vertex0;
	m_Vertex1 = m_PositionMatrix * m_Vertex1;
	m_Vertex2 = m_PositionMatrix * m_Vertex2;

	//Calculate origin with new positionmatrix
	m_Origin = (m_PositionMatrix * Elite::FPoint4(m_Origin)).xyz;
}

//Pure virtual function to check if the ray has a hit
bool Triangle::Hit(const Ray& ray, HitRecord& hitRecord)
{
	//Check if we intersect with the plane of the triangle
	if (Elite::Dot(m_Normal, ray.direction) == 0) return false;

	//Switch case for the cull mode
	switch (m_CullMode)
	{
	case CullMode::BackFaceCulling:
		if (Elite::Dot(m_Normal, ray.direction) > 0) return false;	//We don't want to hit the backface of the triangle so we return no hit when this happens
		break;
	case CullMode::FrontFaceCulling:
		if (Elite::Dot(m_Normal, ray.direction) < 0) return false;	//We don't want to hit the frontface of the triangle so we return no hit when this happens
		break;
	case CullMode::NoCulling:
		break;
	default:
		break;
	}

	//Initialze vector and tValue
	const Elite::FVector3 L = m_Origin - ray.origin;
	const float tValue = Elite::Dot(L, m_Normal) / Elite::Dot(ray.direction, m_Normal);
	//If tValue is not between the tValues of the ray return no hit
	if (tValue < ray.tMin || tValue > ray.tMax || tValue > hitRecord.tValue) return false;

	//Initialze the hitpoint of the ray
	const Elite::FPoint3 hitPoint = ray.origin + tValue * ray.direction;
	Elite::FVector3 pointToSide{}; //!!!!!! different vertex depending on the edge !!!!!!//

	//Initialize an edge an calculate the vector from the hitpoint to a vertex
	const Elite::FVector4 edgeA = m_Vertex1 - m_Vertex0;
	pointToSide = hitPoint - m_Vertex0.xyz;
	//If the dot with the triangles normal and their vector is smaller than 0 the hitpoint is on the wrong side so there is no hit
	if (Elite::Dot(m_Normal, Elite::Cross(edgeA.xyz, pointToSide)) < 0) return false;

	//Initialize an edge an calculate the vector from the hitpoint to a vertex
	const Elite::FVector4 edgeB = m_Vertex2 - m_Vertex1;
	pointToSide = hitPoint - m_Vertex1.xyz;
	//If the dot with the triangles normal and their vector is smaller than 0 the hitpoint is on the wrong side so there is no hit
	if (Elite::Dot(m_Normal, Elite::Cross(edgeB.xyz, pointToSide)) < 0) return false;

	//Initialize an edge an calculate the vector from the hitpoint to a vertex
	const Elite::FVector4 edgeC = m_Vertex0 - m_Vertex2;
	pointToSide = hitPoint - m_Vertex2.xyz;
	//If the dot with the triangles normal and their vector is smaller than 0 the hitpoint is on the wrong side so there is no hit
	if (Elite::Dot(m_Normal, Elite::Cross(edgeC.xyz, pointToSide)) < 0) return false;

	//If there is a hit copy the variables into the hitrecord and return a hit
	hitRecord.hitPoint = hitPoint;
	hitRecord.normal = m_Normal;
	hitRecord.tValue = tValue;
	return true;
}

//Virtual function to rotate the triangles
void Triangle::Rotation(float elapsedTime, float totalTime, bool clockwise, bool cosineRotation)
{
	//Initialize rotating angle
	float angle{ Elite::ToRadians((float)E_PI) };
	//If rotation is in the opposite way take the opposite of the angle
	if (clockwise) angle = -angle;

	//Make a rotation with the angle
	const Elite::FMatrix4 rotationMatrix = Elite::MakeRotationY(angle * elapsedTime * 5.f);
	const Elite::FMatrix4 cosineRotationMatrix = Elite::MakeRotationY(cosf(totalTime) * elapsedTime * 3.2f);

	//Initialize the inverse position matrix to put it back on the correct place
	const Elite::FMatrix4 inversePositionMatrix = Elite::Inverse(m_PositionMatrix);

	Elite::FMatrix4 centerRotation{};
	if (cosineRotation) centerRotation = m_PositionMatrix * cosineRotationMatrix * inversePositionMatrix;
	else centerRotation = m_PositionMatrix * rotationMatrix * inversePositionMatrix;


	//Calculate new vertex positions and angles with the matrices
	m_Vertex0 = centerRotation * m_Vertex0;
	m_Vertex1 = centerRotation * m_Vertex1;
	m_Vertex2 = centerRotation * m_Vertex2;

	//Calculate new normal and origin
	if (cosineRotation) m_Normal = (cosineRotationMatrix * Elite::FVector4(m_Normal)).xyz;
	else m_Normal = (rotationMatrix * Elite::FVector4(m_Normal)).xyz;
	m_Origin = (centerRotation * Elite::FPoint4(m_Origin)).xyz;
}