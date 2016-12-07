#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>
#include "IVertexBuff.h"
#include "IVertexIndexBuff.h"
namespace render
{
	class IDevice : public SDObject
	{
		public:
			virtual IVertexBuff* createVertexBuff(int byteLen, void* initData, E_VERTEX_TYPE vType) = 0;
			virtual IVertexIndexBuff* createVertexIndexBuff(int byteLen, void* initData, E_INDEX_TYPE iType) = 0;
			virtual ~IDevice();
			virtual bool initDevice(CCreationParams& params) = 0;
			virtual void onResize(CCreationParams& params) = 0;
			virtual bool beginScene(bool backBuffer = true, bool zBuffer = true,\
				const sdmath::vec4& color = sdmath::vec4(0.0f, 0.0f, 0.0f, 1.0f)) = 0;
			virtual void endScene() = 0;
	};

	IDevice* createDevice(CCreationParams& params);
}

