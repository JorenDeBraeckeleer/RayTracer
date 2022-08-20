#include "SceneGraphManager.h"

//Singleton
SceneGraphManager* SceneGraphManager::m_pSceneGraphManager{ nullptr };

//Constructor
SceneGraphManager::SceneGraphManager()
	: m_pSceneGraphs{}
	, m_SceneGraphIndex{0}
{
}

//Destructor
SceneGraphManager::~SceneGraphManager()
{
	//Loop over scenes
	for (SceneGraph* pSceneGraph : m_pSceneGraphs)
	{
		//Delete scenes
		delete pSceneGraph;
		pSceneGraph = nullptr;
	}
}

//Singleton
SceneGraphManager* SceneGraphManager::GetInstance()
{
	//If no scenemanager is made yet, make one
	if (m_pSceneGraphManager == nullptr)
	{
		m_pSceneGraphManager = new SceneGraphManager();
	}
	return m_pSceneGraphManager;
}

//Singleton
void SceneGraphManager::Cleanup()
{
	//Delete scenemanager
	delete m_pSceneGraphManager;
	m_pSceneGraphManager = nullptr;
}

//Add scene
void SceneGraphManager::AddSceneGraph(SceneGraph* pSceneGraph)
{
	m_pSceneGraphs.push_back(pSceneGraph);
}

//Get certain scene
SceneGraph* SceneGraphManager::GetSceneGraph(int sceneGraphIndex) const
{
	return m_pSceneGraphs[sceneGraphIndex];
}

//Get active scene
SceneGraph* SceneGraphManager::GetActiveSceneGraph() const
{
	return m_pSceneGraphs[m_SceneGraphIndex];
}

//Switch to next scene
void SceneGraphManager::UpComingScene()
{
	//If there is no next scene load the first one
	if (m_SceneGraphIndex >= m_pSceneGraphs.size() - 1)
	{
		m_SceneGraphIndex = 0;
	}
	//Load the next scene
	else
	{
		++m_SceneGraphIndex;
	}
}

//Switch to previous scene
void SceneGraphManager::PastScene()
{
	//If there is no previous scene load the last one
	if (m_SceneGraphIndex <= 0)
	{
		m_SceneGraphIndex = (int)m_pSceneGraphs.size() - 1;
	}
	//Load the previous scene
	else
	{
		--m_SceneGraphIndex;
	}
}