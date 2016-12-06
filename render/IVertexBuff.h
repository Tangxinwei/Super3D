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
	public:
		IVertexBuff(uint32_t len) : byteLen(len), SDObject(){}
	};
}

