#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>

namespace render
{
	class IVertexIndexBuff : public SDObject
	{
	protected:
		uint32_t byteLen;
	public:
		IVertexIndexBuff(uint32_t len) : byteLen(len) {}
		virtual ~IVertexIndexBuff(){}
	};
}

