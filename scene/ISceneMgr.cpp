#include "ISceneMgr.h"
#include <render\ShaderDefs.h>
namespace scene
{
	ISceneMgr::~ISceneMgr()
	{
		vector<IScene*>::iterator it = sceneList.begin();
		while (it != sceneList.end())
		{
			(*it)->Release();
			it++;
		}
		sceneList.clear();
	}
	IScene* ISceneMgr::createScene()
	{
		IScene* scene = new IScene(this);
		scene->autoRelease();
		sceneList.push_back(scene);
		scene->retain();
		return scene;
	}
	
	IModel* ISceneMgr::createModel(SimpleVertex* vertex, int vertexCount, uint16_t* index, int indexCount, \
				InputLayout* inputLayout, int inputElementNumber, char* vsFileName, char* psFileName, E_SHADER_TYPE shaderType)
	{
		IDevice* pDevice = getDeviceInstance();
		IVertexBuff* vertexBuff = pDevice->createVertexBuff(sizeof(SimpleVertex) * vertexCount, vertex, EVT_SIMPLE);
		vertexBuff->autoRelease();
		IVertexIndexBuff* indexBuff = pDevice->createVertexIndexBuff(sizeof(uint16_t) * indexCount, index, EIT_16BIT);
		indexBuff->autoRelease();
		IVertexShader* vs = pDevice->createVertexShader(vsFileName, "vs_main", inputLayout, inputElementNumber, shaderType);
		vs->autoRelease();
		IPixelShader* ps = pDevice->createPixelShader(psFileName, "ps_main");
		ps->autoRelease();
		IModel* model = new IModel(vertexBuff, indexBuff, vs, ps);
		model->autoRelease();
		return model;
	}

	ICamera* ISceneMgr::createCamera(float fov, float aspect, float near, float far)
	{
		ICamera* camera = new MoveCamera(2, fov, aspect, near, far);
		camera->autoRelease();
		return camera;
	}

	void ISceneMgr::testInit()
	{
		IScene* scene = createScene();
		IDevice* pDevice = getDeviceInstance();
		sdmath::vec4 color(1, 0, 1, 1);
		const float factor = 1.0;
		SimpleVertex vertex[4] =
		{
			SimpleVertex(sdmath::vec3(-1 * factor, 1 * factor, 0.1), color), SimpleVertex(sdmath::vec3(-1 * factor, -1 * factor, 0.1), color),\
			SimpleVertex(sdmath::vec3(1 * factor, -1 * factor, 0.1), color), SimpleVertex(sdmath::vec3(1 * factor, 1 * factor, 0.1), color),
		};
		uint16_t index[6] = {
			0, 2, 3,\
			0, 1, 2
		};
		IModel* model = createModel(vertex, 4, index, 6, SimpleVertexHLSL::VS_INPUT_LAYOUT::input, 2, "../../shader/dx11/simpleVertex_vs.hlsl", \
				"../../shader/dx11/simpleVertex_ps.hlsl", EST_SIMPLE);
		scene->addModel(model);
		model->rotateZ(3.1415926 / 8);
		vec2 windowSize = pDevice->getWindowSize();
		ICamera* camera = createCamera(3.1415 / 2, windowSize[0] / windowSize[1], 1, 1000);
		scene->addCamera(camera);
		camera->translate(0, 0, -3);
	}
}