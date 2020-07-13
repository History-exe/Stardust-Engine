#include <GFX/RenderCore.h>
#include <GFX/GFXWrapper.h>

namespace Stardust::GFX {
	RenderCore::RenderCore()
	{
		r = g = b = a = 0;
	}
	RenderCore::~RenderCore()
	{
		r = g = b = a = 0;
	}
	void RenderCore::init()
	{
		Platform::detail::Graphics::initGraphicsContext();
	}
	void RenderCore::cleanup()
	{
		Platform::detail::Graphics::cleanupGraphicsContext();
	}

	void RenderCore::clear()
	{
		gfxClear(GFX_COLOR_BUFFER | GFX_DEPTH_BUFFER | GFX_STENCIL_BUFFER);
	}
	void RenderCore::setClearColor(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;

		gfxClearColor(((float)r)/255.0f, ((float)g)/255.0f, ((float)b)/255.0f, ((float)a)/255.0f); 
	}

	void RenderCore::setClearColor(float _r, float _g, float _b, float _a)
	{
		r = _r * 255.0f;
		g = _g * 255.0f;
		b = _b * 255.0f;
		a = _a * 255.0f;
		gfxClearColor(_r, _g, _b, _a);
	}

	void RenderCore::set2DMode(float bottom, float top, float left, float right, float znear, float zfar)
	{
		gfxSetOrtho(bottom, top, left, right, znear, zfar);
	}

	void RenderCore::beginFrame()
	{
		Platform::detail::Graphics::beginFrame();
	}
	void RenderCore::endFrame()
	{
		Platform::detail::Graphics::endFrame();
	}

	RenderCore* g_RenderCore = nullptr;
}