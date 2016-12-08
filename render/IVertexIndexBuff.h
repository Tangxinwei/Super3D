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
		uint32_t count;
	public:
		IVertexIndexBuff(uint32_t len, E_INDEX_TYPE i, uint32_t c) : byteLen(len), iType(i), count(c), SDObject() {}
		virtual ~IVertexIndexBuff(){}
		virtual void* getBuff() = 0;
		E_INDEX_TYPE getIndexType() { return iType; }
		uint32_t getIndexCount() { return count; }
	};
}

