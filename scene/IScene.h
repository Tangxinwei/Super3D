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
	public:
		mat4 g_viewMatrix;
		mat4 g_viewProjectionMatrix;
		IScene(ISceneMgr* p) : pSceneMgr(p){}
		~IScene();
		bool addModel(IModel* model);
		bool addCamera(ICamera* camera);
		void update(float dt);
		void render();
	};
}

