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
	public:
		IModel(IVertexBuff* v, IVertexIndexBuff* pI, IVertexShader* pVS, IPixelShader* pPS);
		void render();
		virtual ~IModel();
	};
}

