#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <vector>
#include "IScene.h"
#include "IModel.h"
using namespace render;
using namespace std;

namespace scene
{
	class ISceneMgr : public SDObject
	{
	protected:
		vector<SDObject*> gcList;
		vector<IScene*> sceneList;
		IDevice* pDevice;
	public:
		void testInit();
		ISceneMgr(IDevice* p) : pDevice(p) 
		{
			testInit();
		}
		virtual ~ISceneMgr();
		IModel* createModel(SimpleVertex* vertex, int vertexCount, uint16_t* index, int indexCount);
		IScene* createScene();
		template <class T>
		T* addToGcList(T* object)
		{
			gcList.push_back(object);
			return object;
		}
		void update()
		{
			vector<SDObject*>::iterator it = gcList.begin();
			while (it != gcList.end())
			{
				(*it)->Release();
				it++;
			}
			gcList.clear();
		}
		void render()
		{
			pDevice->beginScene();
			vector<IScene*>::iterator it = sceneList.begin();
			while (it != sceneList.end())
			{
				(*it)->render(pDevice);
				it++;
			}
			pDevice->endScene();
		}
	};
}

