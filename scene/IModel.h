#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <render\SD3DVertex.h>
#include <render\IVertexShader.h>
#include <render\IPixelShader.h>
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
		IVertexShader* pVertexShader;
		IPixelShader* pPixelShader;
		IScene* pScene;
	public:
		IModel(IVertexBuff* v, IVertexIndexBuff* pI, IVertexShader* pVS, IPixelShader* pPS) : pVertex(v), pIndex(pI), \
			pScene(NULL), pVertexShader(pVS), pPixelShader(pPS)
		{
			pVertex->retain();
			pIndex->retain();
			pVertexShader->retain();
			pPixelShader->retain();
		}
		void render(IDevice* pDevice)
		{
			pDevice->setPSShader(pPixelShader);
			pDevice->setVSShader(pVertexShader);
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

