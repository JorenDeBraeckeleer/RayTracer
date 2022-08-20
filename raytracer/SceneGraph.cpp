#include "SceneGraph.h"
#include <typeinfo>
#include "PointLight.h"
#include "DirectionalLight.h"

//Constructor
SceneGraph::SceneGraph()
	: m_pObjects{}
	, m_pLights{}
{
}

//Destructor
SceneGraph::~SceneGraph()
{
	//Loop over all objects
	for (Object* pObject : m_pObjects)
	{
		//Delete objects
		delete pObject;
		pObject = nullptr;
	}
	//Loop over all lights
	for (Light* lights : m_pLights)
	{
		//Dlete lights
		delete lights;
		lights = nullptr;
	}
}

//Add object
void SceneGraph::AddObjectToGraph(Object* pObject)
{
	m_pObjects.push_back(pObject);
}

//Add light
void SceneGraph::AddLightToScene(Light* pLight)
{
	m_pLights.push_back(pLight);
}

//Get objects
const std::vector<Object*>& SceneGraph::GetObjects() const
{
	return m_pObjects;
}

//Get lights
const std::vector<Light*>& SceneGraph::GetLights() const
{
	return m_pLights;
}