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
		IScene* scene = addToGcList(new IScene(this));
		sceneList.push_back(scene);
		scene->retain();
		return scene;
	}
	
	IModel* ISceneMgr::createModel(SimpleVertex* vertex, int vertexCount, uint16_t* index, int indexCount, \
				InputLayout* inputLayout, int inputElementNumber, char* vsFileName, char* psFileName)
	{
		IVertexBuff* vertexBuff = pDevice->createVertexBuff(sizeof(SimpleVertex) * vertexCount, vertex, EVT_SIMPLE);
		addToGcList(vertexBuff);
		IVertexIndexBuff* indexBuff = pDevice->createVertexIndexBuff(sizeof(uint16_t) * indexCount, index, EIT_16BIT);
		addToGcList(indexBuff);
		IVertexShader* vs = pDevice->createVertexShader(vsFileName, "vs_main", inputLayout, inputElementNumber);
		addToGcList(vs);
		IPixelShader* ps = pDevice->createPixelShader(psFileName, "ps_main");
		addToGcList(ps);
		return addToGcList(new IModel(vertexBuff, indexBuff, vs, ps));
	}

	ICamera* ISceneMgr::createCamera(float fov, float aspect, float near, float far)
	{
		return addToGcList(new ICamera(fov, aspect, near, far));
	}

	void ISceneMgr::testInit()
	{
		IScene* scene = createScene();
		sdmath::vec4 color(1, 1, 1, 1);
		SimpleVertex vertex[4] =
		{
			SimpleVertex(sdmath::vec3(-1, 0, 1), color), SimpleVertex(sdmath::vec3(-1, 0, -1), color),\
			SimpleVertex(sdmath::vec3(1, 0, -1), color), SimpleVertex(sdmath::vec3(1, 0, 1), color),
		};
		uint16_t index[6] = {
			0, 3, 2,\
			0, 2, 1
		};
		IModel* model = createModel(vertex, 4, index, 6, SimpleVertexHLSL::VS_INPUT_LAYOUT::input, 2, "../../shader/dx11/simpleVertex.hlsl", "../../shader/dx11/simpleVertex.hlsl");
		scene->addModel(model);
		vec2 windowSize = pDevice->getWindowSize();
		ICamera* camera = createCamera(3.1415 / 2, windowSize[1] / windowSize[0], 1, 1000);
		scene->addCamera(camera);
	}
}