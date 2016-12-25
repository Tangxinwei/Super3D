#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <vector>
#include "IModel.h"
#include "ICamera.h"
using namespace render;
using namespace std;
using namespace sdmath;
namespace scene
{
	class ISceneMgr;
	class IScene : public SDObject
	{
	protected:
		ISceneMgr* pSceneMgr;
		vector<IModel*> modelList;
		ICamera* camera;
		mat4 g_viewMatrix;
		mat4 g_viewProjectionMatrix;
	public:
		IScene(ISceneMgr* p) : pSceneMgr(p){}
		~IScene();
		bool addModel(IModel* model)
		{
			if (model->getCurrentScene())
				return false;
			modelList.push_back(model);
			model->retain();
			model->onAddToScene(this);
			return true;
		}
		
		bool addCamera(ICamera* camera)
		{
			if (camera->getCurrentScene())
				return false;
			this->camera = camera;
			camera->retain();
			camera->onAddToScene(this);
			return true;
		}
		void update(){}
		void render(IDevice* pDevice)
		{
			if (camera)
			{
				g_viewMatrix = inverse(camera->getWorldTransform());
				mat4 projectionMatrix = camera->getProjectionMatrix();
				g_viewProjectionMatrix = projectionMatrix * g_viewMatrix;
			}
			pDevice->beginScene();
			vector<IModel*>::iterator it = modelList.begin();
			while (it != modelList.end())
			{
				(*it)->render(pDevice);
				it++;
			}
			pDevice->endScene();
		}
	};
}

