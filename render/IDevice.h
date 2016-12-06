#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>
#include "IVertexBuff.h"
namespace render
{
	class IDevice : public SDObject
	{
		public:
			virtual IVertexBuff* createVertexBuff(int byteLen, void* initData) = 0;
			virtual ~IDevice();
			virtual bool initDevice(CCreationParams& params) = 0;
			virtual void onResize(CCreationParams& params) = 0;
			virtual bool beginScene(bool backBuffer = true, bool zBuffer = true,\
				const sdmath::vec4& color = sdmath::vec4(0.0f, 0.0f, 0.0f, 1.0f)) = 0;
			virtual void endScene() = 0;
			virtual void drawVertexPrimitiveList(const void* vertices, uint32_t vertexCount,\
				const void* indexList, uint32_t primCount, E_VERTEX_TYPE vType = EVT_STANDARD,\
				E_PRIMITIVE_TYPE pType = EPT_TRIANGLES, E_INDEX_TYPE iType = EIT_16BIT) = 0;
			void drawIndexedTriangleList(const SD3DVertex* vertices, uint32_t vertexCount, const uint16_t* indexList, uint32_t triangleCount)
			{
				drawVertexPrimitiveList(vertices, vertexCount, indexList, triangleCount, EVT_STANDARD, EPT_TRIANGLES, EIT_16BIT);
			}
	};

	IDevice* createDevice(CCreationParams& params);
}

