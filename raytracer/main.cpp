//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>
#include <thread>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"

//------------------------------------------------------//
//Manager includes
#include "CameraManager.h"
#include "MaterialManager.h"
#include "SceneGraphManager.h"

//Manager singletons
#define CAMERAMANAGER CameraManager::GetInstance()
#define MATERIALMANAGER MaterialManager::GetInstance()
#define SCENEGRAPHMANAGER SceneGraphManager::GetInstance()
//------------------------------------------------------//

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 640;
	const uint32_t height = 480;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - Joren De Braeckeleer",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer();
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);
	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;
	bool showFPS = false;
	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				if (e.key.keysym.scancode == SDL_SCANCODE_X)
					takeScreenshot = true;

				//------------------------------------------------------------------------------------//
				//Keybindings
				if (e.key.keysym.scancode == SDL_SCANCODE_N ||
					e.key.keysym.scancode == SDL_SCANCODE_B ||
					e.key.keysym.scancode == SDL_SCANCODE_Q ||
					e.key.keysym.scancode == SDL_SCANCODE_E) pRenderer->InfoKeys(e.key.keysym.scancode);

				////ExtraKeybindings
				//Show FPS
				if (e.key.keysym.scancode == SDL_SCANCODE_F)
					showFPS = !showFPS;
				//Show controls
				if (e.key.keysym.scancode == SDL_SCANCODE_C)
					pRenderer->InfoText();
				//------------------------------------------------------------------------------------//
				break;
			default:
				break;
			}
		}

		//-------------------------------------------------------//
		//CameraMovement
		CAMERAMANAGER->GetActiveCamera()->Movement(pTimer->GetElapsed());
		//(Cosine) rotation
		pRenderer->SetTotalTime(pTimer->GetTotal());
		pRenderer->SetElapsedTime(pTimer->GetElapsed());
		//-------------------------------------------------------//

		//--------- Render ---------
		pRenderer->Render();

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			if (showFPS) std::cout << "FPS: " << pTimer->GetFPS() << std::endl;
		}

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();

	//Shutdown "framework"
	delete pRenderer;
	delete pTimer;

	//-------------------------//
	//Delete singletons
	CAMERAMANAGER->Cleanup();
	MATERIALMANAGER->Cleanup();
	SCENEGRAPHMANAGER->Cleanup();
	//-------------------------//

	ShutDown(pWindow);
	return 0;
}