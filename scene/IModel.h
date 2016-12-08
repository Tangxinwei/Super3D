#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <render\SD3DVertex.h>
#include "IEntity.h"
using namespace render;
namespace scene
{
	class IScene;
	class IModel : public IEntity
	{
	protected:
		IVertexBuff* pVertex;
		IVertexIndexBuff* pIndex;
		IScene* pScene;
	public:
		IModel(IVertexBuff* v, IVertexIndexBuff* pI) : pVertex(v), pIndex(pI), pScene(NULL){}
		void render(IDevice* pDevice)
		{
			pDevice->drawIndexedVertexTriangles(pVertex, pIndex);
		}
		IScene* getCurrentScene() { return pScene; }
		void onAddToScene(IScene* scene)
		{
			pScene = scene;
		}
		virtual ~IModel();
	};
}

