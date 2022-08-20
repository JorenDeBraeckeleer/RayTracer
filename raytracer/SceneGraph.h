#pragma once
#include <vector>
#include "Object.h"
#include "Light.h"

class SceneGraph final
{
public:
	SceneGraph();
	//Rule of five
	~SceneGraph();
	SceneGraph(const SceneGraph& sceneGraph) = delete;
	SceneGraph(SceneGraph&& sceneGraph) = delete;
	SceneGraph& operator=(const SceneGraph& sceneGraph) = delete;
	SceneGraph& operator=(SceneGraph&& sceneGraph) = delete;

	//Functions
	void AddObjectToGraph(Object* pObject);
	void AddLightToScene(Light* pLight);

	const std::vector<Object*>& GetObjects() const;
	const std::vector<Light*>& GetLights() const;

private:
	//Variables
	std::vector<Object*> m_pObjects;
	std::vector<Light*> m_pLights;
};