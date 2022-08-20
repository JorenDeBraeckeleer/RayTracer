#pragma once
#include "EMath.h"

class PerspectiveCamera final
{
public:
	PerspectiveCamera(const Elite::FPoint4& cameraPosition);
	//Rule of five
	~PerspectiveCamera() = default;
	PerspectiveCamera(const PerspectiveCamera& perspectiveCamera) = delete;
	PerspectiveCamera(PerspectiveCamera&& perspectiveCamera) = delete;
	PerspectiveCamera& operator=(const PerspectiveCamera& perspectiveCamera) = delete;
	PerspectiveCamera& operator=(PerspectiveCamera&& perspectiveCamera) = delete;

	//Functions
	void Movement(float deltaTime);

	float GetAspectRatio(float screenWidth, float screenHeight) const;
	float GetFOV(float degrees = 45.f) const;
	Elite::FMatrix4 GetCameraMatrix();

private:
	//Private functions
	void CalculateMatrix();
	void CalculateTranslationMatrix();
	void CalculateRotationXMatrix();
	void CalculateRotationYMatrix();
	
	void MoveLeft(float deltaTime);
	void MoveRight(float deltaTime);
	void MoveDown(float deltaTime);
	void MoveUp(float deltaTime);
	void MoveForwards(float deltaTime);
	void MoveBackwards(float deltaTime);
	void MoveRotate(float deltaTime);

	void AdjustCamera(const Elite::FPoint4& cameraPosition);

	//Variables
	Elite::FPoint4 m_CameraPosition;
	Elite::FMatrix4 m_CameraMatrix;
	Elite::FMatrix4 m_RotationXMatrix;
	Elite::FMatrix4 m_RotationYMatrix;

	const Elite::FVector3 m_MoveSpeed;
	const float m_RotateSpeed;
	Elite::FPoint2 m_RotateAngles;
	Elite::IVector2 m_MousePos;

	Elite::FVector3 m_Forward;
	Elite::FVector3 m_Up;
	Elite::FVector3 m_Right;
};