//External includes
#include "SDL.h"
#include "SDL_surface.h"

//Project includes
#include <iostream>

#include "ERenderer.h"
#include "ERGBColor.h"

#include "PerspectiveCamera.h"
#include "CameraManager.h"

#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

#include "Mesh.h"
#include "ObjParser.h"

#include "Light.h"
#include "PointLight.h"
#include "DirectionalLight.h"

#include "SceneGraph.h"
#include "SceneGraphManager.h"

#include "Material.h"
#include "Material_Lambert.h"
#include "Material_LambertPhong.h"
#include "Material_CookTorrenceBRDF.h"
#include "MaterialManager.h"

//--------------------------------------------------------------------//
//Singletons
#define CAMERAMANAGER CameraManager::GetInstance()
#define MATERIALMANAGER MaterialManager::GetInstance()
#define SCENEGRAPHMANAGER SceneGraphManager::GetInstance()
#define ADDSCENEGRAPH SCENEGRAPHMANAGER->AddSceneGraph(new SceneGraph())
#define SCENEGRAPH(int) SCENEGRAPHMANAGER->GetSceneGraph(int)
//--------------------------------------------------------------------//

Elite::Renderer::Renderer(SDL_Window * pWindow)
{
	//Initialize
	m_pWindow = pWindow;
	m_pFrontBuffer = SDL_GetWindowSurface(pWindow);
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;

	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
	////Initializing
	//Show controls
	InfoText();

	//Make materials
	Material* pCookTorrenceRoughMetal = MATERIALMANAGER->AddMaterial(new Material_CookTorrenceBRDF(Elite::RGBColor(0.972f, 0.960f, 0.915f), true, 1.f));
	Material* pCookTorrenceMediumMetal = MATERIALMANAGER->AddMaterial(new Material_CookTorrenceBRDF(Elite::RGBColor(0.972f, 0.960f, 0.915f), true, 0.6f));
	Material* pCookTorrenceSmoothMetal = MATERIALMANAGER->AddMaterial(new Material_CookTorrenceBRDF(Elite::RGBColor(0.972f, 0.960f, 0.915f), true, 0.1f));
	Material* pCookTorrenceRoughPlastic = MATERIALMANAGER->AddMaterial(new Material_CookTorrenceBRDF(Elite::RGBColor(0.75f, 0.75f, 0.75f), false, 1.0f));
	Material* pCookTorrenceMediumPlastic = MATERIALMANAGER->AddMaterial(new Material_CookTorrenceBRDF(Elite::RGBColor(0.75f, 0.75f, 0.75f), false, 0.4f));
	Material* pCookTorrenceSmoothPlastic = MATERIALMANAGER->AddMaterial(new Material_CookTorrenceBRDF(Elite::RGBColor(0.75f, 0.75f, 0.75f), false, 0.1f));
	Material* pLambertGreyBlue = MATERIALMANAGER->AddMaterial(new Material_Lambert(Elite::RGBColor(0.49f, 0.57f, 0.57f), 1.f));
	Material* pLambertWhite = MATERIALMANAGER->AddMaterial(new Material_Lambert(Elite::RGBColor(1.f, 1.f, 1.f), 1.f));

	//Add first scene
	ADDSCENEGRAPH;

	//Add camera
	CAMERAMANAGER->AddCamera(new PerspectiveCamera(Elite::FPoint4(0.f, 3.f, 8.f, 1.f)));

	//Add planes
	SCENEGRAPH(0)->AddObjectToGraph(new Plane{ FPoint3(0.f, 0.f, 0.f), FVector3(0.f, 1.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(0)->AddObjectToGraph(new Plane{ FPoint3(0.f, 0.f, -10.f), FVector3(0.f, 0.f, 1.f), pLambertGreyBlue });
	SCENEGRAPH(0)->AddObjectToGraph(new Plane{ FPoint3(0.f, 10.f, 0.f), FVector3(0.f, -1.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(0)->AddObjectToGraph(new Plane{ FPoint3(5.f, 0.f, 0.f), FVector3(-1.f, 0.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(0)->AddObjectToGraph(new Plane{ FPoint3(-5.f, 0.f, 0.f), FVector3(1.f, 0.f, 0.f), pLambertGreyBlue });

	//Add spheres
	SCENEGRAPH(0)->AddObjectToGraph(new Sphere{ FPoint3(-1.75f, 1.f, 0.f), 0.75f, pCookTorrenceRoughMetal });
	SCENEGRAPH(0)->AddObjectToGraph(new Sphere{ FPoint3(0.f, 1.f, 0.f), 0.75f, pCookTorrenceMediumMetal });
	SCENEGRAPH(0)->AddObjectToGraph(new Sphere{ FPoint3(1.75f, 1.f, 0.f), 0.75f, pCookTorrenceSmoothMetal });
	SCENEGRAPH(0)->AddObjectToGraph(new Sphere{ FPoint3(-1.75f, 3.f, 0.f), 0.75f, pCookTorrenceRoughPlastic });
	SCENEGRAPH(0)->AddObjectToGraph(new Sphere{ FPoint3(0.f, 3.f, 0.f), 0.75f, pCookTorrenceMediumPlastic });
	SCENEGRAPH(0)->AddObjectToGraph(new Sphere{ FPoint3(1.75f, 3.f, 0.f), 0.75f, pCookTorrenceSmoothPlastic });

	//Add triangles
	const FPoint3 vertex0{ -0.75f, 1.5f, 0.f };
	const FPoint3 vertex1{ -0.75f, 0.f, 0.f };
	const FPoint3 vertex2{ 0.75f, 0.f, 0.f };
	SCENEGRAPH(0)->AddObjectToGraph(new Triangle{ FPoint3(-1.75f, 4.5f, 0.f), vertex0, vertex1, vertex2, CullMode::BackFaceCulling, pLambertWhite });
	SCENEGRAPH(0)->AddObjectToGraph(new Triangle{ FPoint3(0.f, 4.5f, 0.f), vertex0, vertex1, vertex2, CullMode::FrontFaceCulling, pLambertWhite });
	SCENEGRAPH(0)->AddObjectToGraph(new Triangle{ FPoint3(1.75f, 4.5f, 0.f), vertex0, vertex1, vertex2, CullMode::NoCulling, pLambertWhite });

	//Add lights
	SCENEGRAPH(0)->AddLightToScene(new PointLight{ FPoint3(0.f, 5.f, -5.f), RGBColor(1.f, 0.61f, 0.45f), 50.f });
	SCENEGRAPH(0)->AddLightToScene(new PointLight{ FPoint3(-2.5f, 5.f, 5.f), RGBColor(1.f, 0.8f, 0.45f), 70.f });
	SCENEGRAPH(0)->AddLightToScene(new PointLight{ FPoint3(2.5f, 2.5f, 5.f), RGBColor(0.34f, 0.47f, 0.68f), 50.f });

	//Add second scene
	ADDSCENEGRAPH;

	//Add camera
	CAMERAMANAGER->AddCamera(new PerspectiveCamera(Elite::FPoint4(-0.5f, 5.f, 8.f, 1.f)));

	//Add planes
	SCENEGRAPH(1)->AddObjectToGraph(new Plane{ FPoint3(0.f, 3.f, 0.f), FVector3(0.f, 1.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(1)->AddObjectToGraph(new Plane{ FPoint3(0.f, 0.f, -10.f), FVector3(0.f, 0.f, 1.f), pLambertGreyBlue });

	//Add mesh
	ObjParser bunnyLowPoly("lowpoly_bunny.obj");
	SCENEGRAPH(1)->AddObjectToGraph(new Mesh{ FPoint3(0.f, 0.f, 0.f), bunnyLowPoly.GetVertexBuffer(), bunnyLowPoly.GetIndexBuffer(), CullMode::NoCulling, pCookTorrenceMediumPlastic });

	//Add lights
	SCENEGRAPH(1)->AddLightToScene(new PointLight{ FPoint3(0.f, 5.f, -6.f), RGBColor(1.f, 1.f, 1.f), 20.f });
	SCENEGRAPH(1)->AddLightToScene(new PointLight{ FPoint3(-2.5f, 5.f, 5.f), RGBColor(1.f, 0.8f, 0.55f), 70.f });
	SCENEGRAPH(1)->AddLightToScene(new PointLight{ FPoint3(2.5f, 2.5f, 5.f), RGBColor(0.66f, 0.53f, 0.62f), 70.f });

	//Add third scene
	ADDSCENEGRAPH;

	//Add camera
	CAMERAMANAGER->AddCamera(new PerspectiveCamera(Elite::FPoint4(0.f, 3.f, 8.f, 1.f)));

	//Add planes
	SCENEGRAPH(2)->AddObjectToGraph(new Plane{ FPoint3(0.f, 0.f, 0.f), FVector3(0.f, 1.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(2)->AddObjectToGraph(new Plane{ FPoint3(0.f, 0.f, -10.f), FVector3(0.f, 0.f, 1.f), pLambertGreyBlue });
	SCENEGRAPH(2)->AddObjectToGraph(new Plane{ FPoint3(0.f, 10.f, 0.f), FVector3(0.f, -1.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(2)->AddObjectToGraph(new Plane{ FPoint3(5.f, 0.f, 0.f), FVector3(-1.f, 0.f, 0.f), pLambertGreyBlue });
	SCENEGRAPH(2)->AddObjectToGraph(new Plane{ FPoint3(-5.f, 0.f, 0.f), FVector3(1.f, 0.f, 0.f), pLambertGreyBlue });

	//Add mesh
	std::vector<Elite::FPoint3> vertexbuf{	Elite::FPoint3(1.f, 0.f, -1.f), Elite::FPoint3(1.f, 0.f, 1.f), Elite::FPoint3(-1.f, 0.f, 1.f), Elite::FPoint3(-1.f, 0.f, -1.f),
											Elite::FPoint3(1.f, 2.f, -1.f), Elite::FPoint3(1.f, 2.f, 1.f),  Elite::FPoint3(-1.f, 2.f, 1.f),  Elite::FPoint3(-1.f, 2.f, -1.f) };
	std::vector<int> indexbuf{ 0,1,2,4,7,6,0,4,5,1,5,2,2,6,3,4,0,3,3,0,2,5,4,6,1,0,5,5,6,2,6,7,3,7,4,3 };
	SCENEGRAPH(2)->AddObjectToGraph(new Mesh{ Elite::FPoint3(0, 0, 0), vertexbuf, indexbuf, CullMode::BackFaceCulling, pCookTorrenceMediumMetal });

	//Add lights
	SCENEGRAPH(2)->AddLightToScene(new PointLight{ FPoint3(0.f, 5.f, -6.f), RGBColor(1.f, 1.f, 1.f), 20.f });
	SCENEGRAPH(2)->AddLightToScene(new PointLight{ FPoint3(-2.5f, 5.f, 5.f), RGBColor(1.f, 0.8f, 0.55f), 70.f });
	SCENEGRAPH(2)->AddLightToScene(new PointLight{ FPoint3(2.5f, 2.5f, 5.f), RGBColor(0.66f, 0.53f, 0.62f), 70.f });
	//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
}

void Elite::Renderer::Render()
{
	//---------------------------------------------------------------------------------------------------//
	////Get variables
	//Get objects and lights in active scene
	const std::vector<Object*>& objects = SCENEGRAPHMANAGER->GetActiveSceneGraph()->GetObjects();
	const std::vector<Light*>& lights = SCENEGRAPHMANAGER->GetActiveSceneGraph()->GetLights();
	
	//Get camera variables for current camera position
	const Elite::FMatrix4 cameraMatrix{ CAMERAMANAGER->GetActiveCamera()->GetCameraMatrix() };
	const Elite::FPoint3 cameraPosition{ cameraMatrix[3].xyz };
	const float aspectRatio{ CAMERAMANAGER->GetActiveCamera()->GetAspectRatio((float)m_Width, (float)m_Height) };
	const float verticalFOV{ CAMERAMANAGER->GetActiveCamera()->GetFOV() };

	//Make ray every second
	Ray ray{};
	//Make object to work with
	Object* pObjectToLight{};
	//---------------------------------------------------------------------------------------------------//
	
	SDL_LockSurface(m_pBackBuffer);

	//Loop over all the pixels  
	for (uint32_t r = 0; r < m_Height; ++r)
	{

		//Transform coordinates to correct space
		const float yss = (1 - 2 * ((r + 0.5f) / m_Height)) * verticalFOV;
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			//-----------------------------------------------------------------------------------------------------------------------------//
			////Pixel loop
			//Make hitrecord every pixel
			HitRecord hitRecord{};

			//Transform coordinates to correct space
			const float xss = (2 * ((c + 0.5f) / m_Width) - 1) * aspectRatio * verticalFOV;
			const FPoint4 toWorldSpace{ xss, yss, -1.f, 1.f };

			//Initialize ray
			ray.origin = (cameraMatrix * toWorldSpace).xyz;
			ray.direction = ray.origin - cameraPosition;
			Elite::Normalize(ray.direction);

			//Make color to work with
			Elite::RGBColor finalColorPixel{};

			//Loop over all objects in current scene
			for (Object* pObject : objects)
			{
				//Look for hit
				if (pObject->Hit(ray, hitRecord))
				{
					//object to work with
					pObjectToLight = pObject;
				}
			}

			//Loop over all lights in current scene
			for (Light* pLight : lights)
			{
				//Initialize lightvector and lightdirection
				const Elite::FVector3 lightVector = pLight->GetVector(hitRecord.hitPoint);
				const float lightVectorLength{ Elite::Magnitude(lightVector) };
				const Elite::FVector3 lightDirection = lightVector / lightVectorLength;
				//Make lambert cosine law
				const float lambertCosineLaw = Elite::Dot(hitRecord.normal, lightDirection);

				//Make boolean to know if you have to apply shadows
				bool hasShadow{};

				//If hard shadows are enabled
				if (m_HasHardShadows)
				{
					//Loop over all objects in scene
					for (Object* pObject : objects)
					{
						//Make ray and hitrecord for lighting
						Ray rayCheckLight{ hitRecord.hitPoint, lightDirection, lightVectorLength };
						HitRecord HitRecordCheckLight{};

						//Look for hit to use shadows
						if (pObject->Hit(rayCheckLight, HitRecordCheckLight)) hasShadow = true;
					}
				}

				//If no shadow and cosine lambert law is valid
				if (lambertCosineLaw > 0 && !hasShadow)
				{
					//Initialize Irradiance
					const Elite::RGBColor eRGB = pLight->GetIrradiance(hitRecord.hitPoint);

					//Initialize BRDF
					Elite::RGBColor brdfRGB{};
					if (pObjectToLight != nullptr) brdfRGB = pObjectToLight->GetMaterial()->Shade(hitRecord, lightDirection, -ray.direction);

					//Switch case, which render mode to use to calculate the color of the pixel
					switch (m_RenderInfo)
					{
					case Elite::Renderer::RenderInfo::BRDF:
						finalColorPixel += brdfRGB * lambertCosineLaw;
						break;
					case Elite::Renderer::RenderInfo::Irradiance:
						finalColorPixel += eRGB * lambertCosineLaw;
						break;
					case Elite::Renderer::RenderInfo::IrradianceAndBDRF:
						finalColorPixel += eRGB * brdfRGB * lambertCosineLaw;
						break;
					default:
						break;
					}
				}
			}

			//If values are higher than 1, MaxToOne will reduce the max value to one and will keep the current ratio of rgb values
			finalColorPixel.MaxToOne();
			//Initialize and show color
			uint32_t uColor{ GetSDL_ARGBColor(finalColorPixel) };
			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(uColor >> 16),
				static_cast<uint8_t>(uColor >> 8),
				static_cast<uint8_t>(uColor));
			//-----------------------------------------------------------------------------------------------------------------------------//
		}
	}

	//-------------------------------------------------------------------//
	//Loop over objects in scene
	for (Object* pObject : objects)
	{
		//Rotate all objects (anti)clockwise
		pObject->Rotation(m_ElapsedTime, m_TotalTime, m_IsRotatingClockwise, m_IsRotatingWithCosine);
	}
	//-------------------------------------------------------------------//

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

//--------------------------------------------------------------------------------------------------------------------------------------------//
////Extra functions
//Keybindings
void Elite::Renderer::InfoKeys(SDL_Scancode key)
{
	if (key == SDL_SCANCODE_N)
	{
		//Switch to next scene
		SCENEGRAPHMANAGER->UpComingScene();
		CAMERAMANAGER->UpComingCamera();
	}
	else if (key == SDL_SCANCODE_B)
	{
		//Switch to previous scene
		SCENEGRAPHMANAGER->PastScene();
		CAMERAMANAGER->PastCamera();
	}
	
	if (key == SDL_SCANCODE_Q)
	{
		//Toggle shadows
		m_HasHardShadows = !m_HasHardShadows;
	}

	if (key == SDL_SCANCODE_E)
	{
		//Toggle render mode
		switch (m_RenderInfo)
		{
		case Elite::Renderer::RenderInfo::BRDF:
			m_RenderInfo = RenderInfo::Irradiance;
			std::cout << "RenderInfo shown is Irradiance only" << std::endl;
			break;
		case Elite::Renderer::RenderInfo::Irradiance:
			m_RenderInfo = RenderInfo::IrradianceAndBDRF;
			std::cout << "RenderInfo shown is both IrradianceAndBRDF" << std::endl;
			break;
		case Elite::Renderer::RenderInfo::IrradianceAndBDRF:
			m_RenderInfo = RenderInfo::BRDF;
			std::cout << "RenderInfo shown is BRDF only" << std::endl;
			break;
		default:
			break;
		}
	}
}

//Show controls
void Elite::Renderer::InfoText()
{
	//Output controls in console
	std::cout <<
		"---------------------------------------------------------------------------------------\n" <<
		"|  \t\t\t\t\t\t\t\t\t\t      |\n" <<
		"|   GameGraphicsProgramming - Milestone - Raytracer - Joren De Braeckeleer - 2GD06E   |\n" <<
		"|  \t\t\t\t\t\t\t\t\t\t      |\n" <<
		"---------------------------------------------------------------------------------------\n" <<
		"_Show FPS: F\t/    _Screenshot: X\n\n"
		"CONTROLS(C):\n" <<
		"    Mouse:\n" <<
		"\t-Rotate:\n\t    RMB + MouseMove-X: Yaw\n\t    RMB + MouseMove-Y: Pitch\n\t    LMB + MouseMove-X: Yaw\n" <<
		"\t-Moving:\n\t    LMB + MouseMove - Y: Forward / Backward\n\t    LMB + RMB + MouseMove - Y: Up / Down\n" <<
		"    KeyBoard:\n" <<
		"\t-Scene:\n\t    N: Next scene\n\t    B: back one scene\n" <<
		"\t-Rendering:\n\t    Q: Toggle shadows\n\t    E: Togle light-equation terms\n" <<
		"\t-Moving:\n\t    W: Forward (Arrow up)\n\t    A: Left (Arrow left)\n\t    S: Backward (Arrow down)\n\t    D: Right (Arrow right)\n" <<
		std::endl;
}
//--------------------------------------------------------------------------------------------------------------------------------------------//