#pragma once
#include <common\CCreationParams.h>
#include <render\IDevice.h>
#include <scene\ISceneMgr.h>
#include <common\CTimer.h>
class CMainWindow
{
protected:
	CCreationParams createParams;
	render::IDevice *pDevice;

public:
	virtual ~CMainWindow() { }
	virtual bool initWindow(CCreationParams& params)
	{
		this->createParams = params;
		this->pDevice = render::createDevice(params);	
		return this->pDevice != NULL;
	}
	virtual bool run() = 0;
	virtual void* getWindowHandler() = 0;
	void mainLoop()
	{
		while (this->run())
		{
			scene::ISceneMgr* pSceneMgr = scene::ISceneMgr::getInstance();
			FrameTimer* t = FrameTimer::getInstance();
			t->update();
			float dt = float(t->getFrameDeltaTime()) / 1000.0;
			pSceneMgr->update(dt);
			pSceneMgr->render();
		}
	}
};

CMainWindow* createMainWindow(render::DeviceType dt);
CMainWindow* getMainWindowInstance();