#include "ISceneMgr.h"

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

	IModel* ISceneMgr::createModel(SimpleVertex* vertex, int vertexCount, uint16_t* index, int indexCount)
	{
		IVertexBuff* vertexBuff = pDevice->createVertexBuff(sizeof(SimpleVertex) * vertexCount, vertex, EVT_SIMPLE);
		IVertexIndexBuff* indexBuff = pDevice->createVertexIndexBuff(sizeof(uint16_t) * indexCount, index, EIT_16BIT);
		return addToGcList(new IModel(vertexBuff, indexBuff));
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
		IModel* model = createModel(vertex, 4, index, 6);
		scene->addModel(model);
	}
}