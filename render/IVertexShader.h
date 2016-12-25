#pragma once
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include <vector>
#include "IBuffer.h"
using namespace std;

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
		virtual ~IVertexShader()
		{
			
		}

	};
}

