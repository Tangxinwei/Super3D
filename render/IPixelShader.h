#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "SD3DVertex.h"
#include <math\sdmath.h>

namespace render
{
	class IPixelShader : public SDObject
	{
	public:
		virtual ~IPixelShader(){}
	};
}

