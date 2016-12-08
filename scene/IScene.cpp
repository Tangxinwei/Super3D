#include "IScene.h"

namespace scene
{
	IScene::~IScene()
	{
		vector<IModel*>::iterator it = modelList.begin();
		while (it != modelList.end())
		{
			(*it)->Release();
			it++;
		}
		modelList.clear();
		pSceneMgr = NULL;
	}
}