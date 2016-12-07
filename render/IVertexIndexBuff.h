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
		E_INDEX_TYPE iType;
	public:
		IVertexIndexBuff(uint32_t len, E_INDEX_TYPE i) : byteLen(len), iType(i), SDObject() {}
		virtual ~IVertexIndexBuff(){}
		E_INDEX_TYPE getIndexType() { return iType; }
	};
}

