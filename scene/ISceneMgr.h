#pragma once
#include <util\Function.hpp>
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <vector>
#include "IScene.h"
#include "IModel.h"
#include "ICamera.h"
#include "input\IInput.h"
using namespace render;
using namespace std;

namespace scene
{
	class ISceneMgr : public SingletonBase<ISceneMgr>
	{
	public:
		void doInit()
		{
			testInit();
		}
	protected:
		vector<IScene*> sceneList;
		
	public:
		void testInit();
		virtual ~ISceneMgr();
		IModel* createModel(SimpleVertex* vertex, int vertexCount, uint16_t* index, int indexCount, \
					InputLayout* inputLayout, int inputElementNumber, char* vsFileName, char* psFileName, E_SHADER_TYPE shaderType);
		ICamera* createCamera(float fov, float aspect, float near, float far);
		IScene* createScene();

		void update(float dt)
		{
			InputEventDevice* input = getInputEventDeviceInstance();
			input->updateState();
			MemPool::getInstance()->releaseAll();
			for (IScene* scene : sceneList)
				scene->update(dt);
		}
		void render()
		{
			IDevice* pDevice = getDeviceInstance();
			pDevice->beginScene();
			for (IScene* scene : sceneList)
			{
				scene->render();
			}
			pDevice->endScene();
		}
	};
}

