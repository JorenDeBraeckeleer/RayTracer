#include "CameraManager.h"

//Singleton
CameraManager* CameraManager::m_pCameraManager{ nullptr };

//Constructor
CameraManager::CameraManager()
	: m_pPerspectiveCameras{}
	, m_ActiveIndex{0}
{
}

//Destructor
CameraManager::~CameraManager()
{
	//Loop over cameras
	for (PerspectiveCamera* pPerspectiveCamera : m_pPerspectiveCameras)
	{
		//Delete cameras
		delete pPerspectiveCamera;
		pPerspectiveCamera = nullptr;
	}
}

//Singleton
CameraManager* CameraManager::GetInstance()
{
	//If no cameramanager has been made yet, make a new cameramanager
	if (m_pCameraManager == nullptr)
	{
		m_pCameraManager = new CameraManager();
	}
	return m_pCameraManager;
}

//Singleton
void CameraManager::Cleanup()
{
	//Delete cameramanager
	delete m_pCameraManager;
	m_pCameraManager = nullptr;
}

//Add camera
void CameraManager::AddCamera(PerspectiveCamera* pPerspectiveCamera)
{
	m_pPerspectiveCameras.push_back(pPerspectiveCamera);
}

//Get active camera
PerspectiveCamera* CameraManager::GetActiveCamera() const
{
	return m_pPerspectiveCameras[m_ActiveIndex];
}

PerspectiveCamera* CameraManager::GetCamera(int index) const
{
	return m_pPerspectiveCameras[index];
}

//Switch to next scene
void CameraManager::UpComingCamera()
{
	//If there is no next scene load the first one
	if (m_ActiveIndex >= m_pPerspectiveCameras.size() - 1)
	{
		m_ActiveIndex = 0;
	}
	//Load the next scene
	else
	{
		++m_ActiveIndex;
	}
}

//Switch to previous scene
void CameraManager::PastCamera()
{
	//If there is no previous scene load the last one
	if (m_ActiveIndex <= 0)
	{
		m_ActiveIndex = (int)m_pPerspectiveCameras.size() - 1;
	}
	//Load the previous scene
	else
	{
		--m_ActiveIndex;
	}
}