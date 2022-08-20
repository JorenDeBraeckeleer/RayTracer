#pragma once
#include <vector>
#include "SceneGraph.h"

class SceneGraphManager final
{
public:
	SceneGraphManager();
	//Rule of five
	~SceneGraphManager();
	SceneGraphManager(const SceneGraphManager& sceneGraphManager) = delete;
	SceneGraphManager(SceneGraphManager&& sceneGraphManager) = delete;
	SceneGraphManager& operator=(const SceneGraphManager& sceneGraphManager) = delete;
	SceneGraphManager& operator=(SceneGraphManager&& sceneGraphManager) = delete;

	//Singleton
	static SceneGraphManager* GetInstance();
	void Cleanup();

	//Functions
	void AddSceneGraph(SceneGraph* pSceneGraph);
	void UpComingScene();
	void PastScene();

	SceneGraph* GetSceneGraph(int sceneGraphIndex) const;
	SceneGraph* GetActiveSceneGraph() const;

private:
	//Variables
	std::vector<SceneGraph*> m_pSceneGraphs;
	int m_SceneGraphIndex;

	//Singleton
	static SceneGraphManager* m_pSceneGraphManager;
};

