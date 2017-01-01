#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>
#include "IVertexBuff.h"
#include "IVertexIndexBuff.h"
#include "IVertexShader.h"
#include "IPixelShader.h"
#include "IBuffer.h"
namespace render
{
	class IDevice : public SDObject
	{
		public:
			virtual void setBufferContent(IBuffer* buffer, void* p, uint32_t size) = 0;
			virtual IBuffer* createBuffer(E_CPU_FLAG ecf, E_BIND_FLAG ebf, uint32_t len) = 0;
			virtual IVertexBuff* createVertexBuff(int byteLen, void* initData, E_VERTEX_TYPE vType) = 0;
			virtual IVertexIndexBuff* createVertexIndexBuff(int byteLen, void* initData, E_INDEX_TYPE iType) = 0;
			virtual sdmath::vec2 getWindowSize() = 0;
			virtual ~IDevice();
			virtual bool initDevice(CCreationParams& params) = 0;
			virtual void onResize(CCreationParams& params) = 0;
			virtual bool beginScene(bool backBuffer = true, bool zBuffer = true,\
				const sdmath::vec4& color = sdmath::vec4(0.0f, 0.0f, 0.0f, 1.0f)) = 0;
			virtual void endScene() = 0;
			virtual void drawIndexedVertexTriangles(IVertexBuff* pVertex, IVertexIndexBuff* pIndex) = 0;
			virtual IVertexShader* createVertexShader(const char* fileName, const char* entryName, InputLayout* layout, int elementNumber, E_SHADER_TYPE shaderType) = 0;
			virtual IPixelShader* createPixelShader(const char* filename, const char* entryname) = 0;
			virtual void setVSShader(IVertexShader* vs) = 0;
			virtual void setPSShader(IPixelShader* ps) = 0; 
	};

	IDevice* createDevice(CCreationParams& params);
	IDevice* getDeviceInstance();
}

