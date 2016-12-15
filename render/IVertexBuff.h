#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>

namespace render
{
	class IVertexBuff : public SDObject
	{
	protected:
		uint32_t byteLen;
		uint32_t count;
		E_VERTEX_TYPE vType;
	public:
		IVertexBuff(uint32_t len, E_VERTEX_TYPE v, uint32_t c) : count(c), vType(v), byteLen(len), SDObject(){}
		E_VERTEX_TYPE getVertexType() { return vType; }
		virtual void* getBuff() = 0;
		uint32_t getVertexCount() { return count; }
		virtual ~IVertexBuff() {}
	};
}

