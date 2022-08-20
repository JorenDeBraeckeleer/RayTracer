/*=============================================================================*/
// Copyright 2017-2019 Elite Engine
// Authors: Matthieu Delaere
/*=============================================================================*/
// ERenderer.h: class that holds the surface to render to, does traverse the pixels 
// and traces the rays using a tracer
/*=============================================================================*/
#ifndef ELITE_RAYTRACING_RENDERER
#define	ELITE_RAYTRACING_RENDERER

#include <cstdint>

struct SDL_Window;
struct SDL_Surface;

namespace Elite
{
	class Renderer final
	{
	public:
		Renderer(SDL_Window* pWindow);
		~Renderer() = default;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) noexcept = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) noexcept = delete;

		void Render();
		bool SaveBackbufferToImage() const;

		//---------------------------//
		//Extra functions
		static void RenderMultiThreaded();
		void InfoKeys(SDL_Scancode key);
		void InfoText();

		void SetTotalTime(float totalTime) { m_TotalTime = totalTime; }
		void SetElapsedTime(float elapsedTime) { m_ElapsedTime = elapsedTime; }
		//---------------------------//

	private:
		SDL_Window* m_pWindow = nullptr;
		SDL_Surface* m_pFrontBuffer = nullptr;
		SDL_Surface* m_pBackBuffer = nullptr;
		uint32_t* m_pBackBufferPixels = nullptr;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;

		//-----------------------------------------------------//
		////Extra variables
		//Enum class for different render modes
		enum class RenderInfo
		{
			BRDF,
			Irradiance,
			IrradianceAndBDRF,
		};
		RenderInfo m_RenderInfo = RenderInfo::IrradianceAndBDRF;
		int m_RenderInfoShown = int(m_RenderInfo);

		float m_ElapsedTime = 0.f;
		float m_TotalTime = 0.f;

		//Booleans for toggles
		bool m_HasHardShadows = true;
		bool m_IsRotatingClockwise = false;
		bool m_IsRotatingWithCosine = true;
		//-----------------------------------------------------//
	};
}

#endif