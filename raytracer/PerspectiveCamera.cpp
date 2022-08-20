#include "PerspectiveCamera.h"
#include "SDL.h"

//Constructor
PerspectiveCamera::PerspectiveCamera(const Elite::FPoint4& cameraPosition)
	: m_CameraPosition{cameraPosition}
	, m_CameraMatrix{m_CameraMatrix.Identity()}
	, m_RotationXMatrix{m_RotationXMatrix.Identity()}
	, m_RotationYMatrix{m_RotationYMatrix.Identity()}
	, m_MoveSpeed{Elite::FVector3(5.f, 5.f, 5.f)}
	, m_RotateSpeed{0.1f}
	, m_RotateAngles{}
	, m_MousePos{}
	, m_Forward{Elite::FVector3(0.f, 0.f, 1.f)}
	, m_Up{}
	, m_Right{}
{
	//Initialize cameramatrix
	CalculateMatrix();
}

//Camera movement with keyboard and mouse
void PerspectiveCamera::Movement(float deltaTime)
{
	//Keyboard
	const Uint8* pKeyboardState = SDL_GetKeyboardState(nullptr);

	//Move left and right
	if (pKeyboardState[SDL_SCANCODE_A] || pKeyboardState[SDL_SCANCODE_LEFT])
	{
		MoveLeft(deltaTime);
	}
	else if (pKeyboardState[SDL_SCANCODE_D] || pKeyboardState[SDL_SCANCODE_RIGHT])
	{
		MoveRight(deltaTime);
	}

	//Move forwards and backwards
	if (pKeyboardState[SDL_SCANCODE_W] || pKeyboardState[SDL_SCANCODE_UP])
	{
		MoveForwards(deltaTime);
	}
	else if (pKeyboardState[SDL_SCANCODE_S] || pKeyboardState[SDL_SCANCODE_DOWN])
	{
		MoveBackwards(deltaTime);
	}

	//Mouse
	Uint32 mouseState = SDL_GetRelativeMouseState(&m_MousePos.x, &m_MousePos.y);

	//Move up and down
	if (mouseState & SDL_BUTTON_LMASK && mouseState & SDL_BUTTON_RMASK)
	{
		if (m_MousePos.y < 0)
		{
			MoveUp(deltaTime);
		}
		else if (m_MousePos.y > 0)
		{
			MoveDown(deltaTime);
		}
	}
	//Rotate camera
	else if (mouseState & SDL_BUTTON_RMASK)
	{
		if (m_MousePos.x != 0)
		{
			MoveRotate(deltaTime);
			CalculateRotationYMatrix();
		}
		if (m_MousePos.y != 0)
		{
			MoveRotate(deltaTime);
			CalculateRotationXMatrix();
		}
	}
	//Move and Rotate
	else if (mouseState & SDL_BUTTON_LMASK)
	{
		//Move forwards and backwards
		if (m_MousePos.y != 0)
		{
			if (m_MousePos.y < 0)
			{
				MoveForwards(deltaTime);
			}
			else if (m_MousePos.y > 0)
			{
				MoveBackwards(deltaTime);
			}
		}
		//Rotate camera
		if (m_MousePos.x != 0)
		{
			MoveRotate(deltaTime);
			CalculateRotationYMatrix();
		}
	}
}

//Get aspect ration of window
float PerspectiveCamera::GetAspectRatio(float screenWidth, float screenHeight) const
{
	return screenWidth / screenHeight;
}

//Get FOV of camera
float PerspectiveCamera::GetFOV(float degrees) const
{
	//FOV = tan(radians / 2)
	float radians{ Elite::ToRadians(degrees) };
	return tanf(radians / 2.f);
}

//Get cameramatrix
Elite::FMatrix4 PerspectiveCamera::GetCameraMatrix()
{
	//Update translationmatrix
	CalculateTranslationMatrix();
	return m_CameraMatrix;
}

//Update translation and rotation matrices
void PerspectiveCamera::CalculateMatrix()
{
	CalculateTranslationMatrix();
	CalculateRotationXMatrix();
	CalculateRotationYMatrix();
}
//Calculate translation matrix
void PerspectiveCamera::CalculateTranslationMatrix()
{
	//Initialize world up vector
	Elite::FVector3 worldUp(0.f, 1.f, 0.f);

	//Make right vector
	m_Right = Elite::GetNormalized(Elite::Cross(worldUp, m_Forward));

	m_CameraMatrix.data[0][0] = m_Right.x;
	m_CameraMatrix.data[0][1] = m_Right.y;
	m_CameraMatrix.data[0][2] = m_Right.z;

	//Make up vector
	m_Up = Elite::GetNormalized(Elite::Cross(m_Forward, m_Right));

	m_CameraMatrix.data[1][0] = m_Up.x;
	m_CameraMatrix.data[1][1] = m_Up.y;
	m_CameraMatrix.data[1][2] = m_Up.z;

	//Make forward vector
	m_CameraMatrix.data[2][0] = m_Forward.x;
	m_CameraMatrix.data[2][1] = m_Forward.y;
	m_CameraMatrix.data[2][2] = m_Forward.z;

	//Make camera position vector
	m_CameraMatrix.data[3][0] = m_CameraPosition.x;
	m_CameraMatrix.data[3][1] = m_CameraPosition.y;
	m_CameraMatrix.data[3][2] = m_CameraPosition.z;

	//Add the neutral 0001
	m_CameraMatrix.data[0][3] = 0.f;
	m_CameraMatrix.data[1][3] = 0.f;
	m_CameraMatrix.data[2][3] = 0.f;
	m_CameraMatrix.data[3][3] = 1.f;
}
//Calculate x-axis of the rotation
void PerspectiveCamera::CalculateRotationXMatrix()
{
	//Make a rotation of the camera with the x angle
	m_RotationXMatrix = Elite::MakeRotation(m_RotateAngles.x, Elite::FVector3(m_CameraMatrix[0]));

	//Change forward vector
	m_Forward = (m_RotationXMatrix * Elite::FVector4(m_Forward)).xyz;

	//Reset angle
	m_RotateAngles.x = 0;
}
//Calculate y-axis of the rotation
void PerspectiveCamera::CalculateRotationYMatrix()
{
	//Make a rotation of the camera with the y angle
	m_RotationYMatrix = Elite::MakeRotation(m_RotateAngles.y, Elite::FVector3(m_CameraMatrix[1]));

	//Change forward vector
	m_Forward = (m_RotationYMatrix * Elite::FVector4(m_Forward)).xyz;

	//Reset angle
	m_RotateAngles.y = 0;
}

//Move camera left
void PerspectiveCamera::MoveLeft(float deltaTime)
{
	m_CameraPosition -= m_Right * m_MoveSpeed.x * deltaTime;
	AdjustCamera(m_CameraPosition);
}
//Move camera right
void PerspectiveCamera::MoveRight(float deltaTime)
{
	m_CameraPosition += m_Right * m_MoveSpeed.x * deltaTime;
	AdjustCamera(m_CameraPosition);
}
//Move camera down
void PerspectiveCamera::MoveDown(float deltaTime)
{
	m_CameraPosition -= m_Up * m_MoveSpeed.y * deltaTime;
	AdjustCamera(m_CameraPosition);
}
//Move camera up
void PerspectiveCamera::MoveUp(float deltaTime)
{
	m_CameraPosition += m_Up * m_MoveSpeed.y * deltaTime;
	AdjustCamera(m_CameraPosition);
}
//Move camera forwards
void PerspectiveCamera::MoveForwards(float deltaTime)
{
	m_CameraPosition -= m_Forward * m_MoveSpeed.z * deltaTime;
	AdjustCamera(m_CameraPosition);
}
//Move camera backwards
void PerspectiveCamera::MoveBackwards(float deltaTime)
{
	m_CameraPosition += m_Forward * m_MoveSpeed.z * deltaTime;
	AdjustCamera(m_CameraPosition);
}
//Rotate camera
void PerspectiveCamera::MoveRotate(float deltaTime)
{
	//Initialze velocity (frame-rate independend)
	float velocity{ m_RotateSpeed * deltaTime };
	//Calculate new angle with mouse position and velocity
	m_RotateAngles.x -= m_MousePos.y * velocity;
	m_RotateAngles.y -= m_MousePos.x * velocity;
}

//Calculate new cameramatrix with new cameraposition
void PerspectiveCamera::AdjustCamera(const Elite::FPoint4& cameraPosition)
{
	m_CameraMatrix[3].x = cameraPosition.x;
	m_CameraMatrix[3].y = cameraPosition.y;
	m_CameraMatrix[3].z = cameraPosition.z;
}