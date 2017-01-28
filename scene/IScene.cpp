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

	bool IScene::addModel(IModel* model)
	{
		if (model->getCurrentScene())
			return false;
		modelList.push_back(model);
		model->retain();
		model->onAddToScene(this);
		return true;
	}

	bool IScene::addCamera(ICamera* camera)
	{
		if (camera->getCurrentScene())
			return false;
		this->camera = camera;
		camera->retain();
		camera->onAddToScene(this);
		return true;
	}
	void IScene::update(float dt) 
	{
		if (camera)
			camera->update(dt);
	}

	void IScene::render()
	{
		if (camera)
		{
			g_viewMatrix = inverse(camera->getWorldTransform());
			mat4 projectionMatrix = camera->getProjectionMatrix();
			g_viewProjectionMatrix = projectionMatrix * g_viewMatrix;
		}

		vector<IModel*>::iterator it = modelList.begin();
		while (it != modelList.end())
		{
			(*it)->render();
			it++;
		}

	}
}