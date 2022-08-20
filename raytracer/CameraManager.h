#pragma once
#include <vector>
#include "PerspectiveCamera.h"

class CameraManager final
{
public:
	CameraManager();
	//Rule of five
	~CameraManager();
	CameraManager(const CameraManager& cameraManager) = delete;
	CameraManager(CameraManager&& cameraManager) = delete;
	CameraManager& operator=(const CameraManager& cameraManager) = delete;
	CameraManager& operator=(CameraManager&& cameraManager) = delete;

	//Singleton
	static CameraManager* GetInstance();
	void Cleanup();

	//Functions
	void AddCamera(PerspectiveCamera* pCamera);
	void UpComingCamera();
	void PastCamera();

	PerspectiveCamera* GetActiveCamera() const;
	PerspectiveCamera* GetCamera(int index) const;

private:
	//Variables
	std::vector<PerspectiveCamera*> m_pPerspectiveCameras;
	int m_ActiveIndex;

	//Singleton
	static CameraManager* m_pCameraManager;
};