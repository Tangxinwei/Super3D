#pragma once
#include<memory>
#include "CommonType.h"

class CCreationParams
{
public:
	render::DeviceType deviceType;
	int width;
	int height;
	bool fullScreen;
	bool enable4xMsaa;
	void* windowHandler;
	CCreationParams(render::DeviceType dt = render::DT_DX11, int w = 960, int h = 640, bool fs = false, bool e4m = false) :\
		deviceType(dt), width(w), height(h), fullScreen(fs), enable4xMsaa(e4m), windowHandler(0)
	{

	}
	CCreationParams(CCreationParams& params)
	{
		memcpy(this, &params, sizeof(CCreationParams));
	}
};