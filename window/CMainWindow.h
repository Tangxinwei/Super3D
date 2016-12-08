#pragma once
#include <common\CCreationParams.h>
#include <render\IDevice.h>
#include <scene\ISceneMgr.h>
class CMainWindow
{
protected:
	CCreationParams createParams;
	render::IDevice *pDevice;
	scene::ISceneMgr *pSceneMgr;

public:
	virtual ~CMainWindow() { SafeRelease(pDevice); SafeRelease(pSceneMgr); }
	virtual bool initWindow(CCreationParams& params)
	{
		this->createParams = params;
		this->pDevice = render::createDevice(params);
		if (this->pDevice != NULL)
			this->pSceneMgr = new scene::ISceneMgr(pDevice);
		return this->pDevice != NULL;
	}
	virtual bool run() = 0;
	virtual void* getWindowHandler() = 0;
	void mainLoop()
	{
		while (this->run())
		{
			pSceneMgr->update();
			pSceneMgr->render();
		}
	}
};