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
		E_VERTEX_TYPE vType;
	public:
		IVertexBuff(uint32_t len, E_VERTEX_TYPE v) : vType(v), byteLen(len), SDObject(){}
		E_VERTEX_TYPE getVertexBuff() { return vType; }
	};
}

