#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>

namespace render
{
	struct InputLayout
	{
		const char* semanticName;
		unsigned int semanticIndex;
		E_GIFORMAT_TYPE gi_format;
		unsigned int inputSlot;
		unsigned int inputByteOffset;
	};

	class IVertexShader : public SDObject
	{
	public:
		virtual ~IVertexShader(){}
	};
}

