#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <vector>
#include "IModel.h"
using namespace render;
using namespace std;
namespace scene
{
	class ISceneMgr;
	class IScene : public SDObject
	{
	protected:
		ISceneMgr* pSceneMgr;
		vector<IModel*> modelList;
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
		void update(){}
		void render(IDevice* pDevice)
		{
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

