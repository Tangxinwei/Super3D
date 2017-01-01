#pragma once

#include <math\sdmath.h>
using namespace sdmath;
#include <common\CommonType.h>
#include "IVertexShader.h"

namespace render
{
	namespace SimpleVertexHLSL
	{
		class cbPerObject
		{
		public:
			mat4 g_worldViewPorjection;
			mat4 g_world;
		};

		class VS_INPUT_LAYOUT
		{
		public:
			static InputLayout input[2];
		};
		int setParams(IVertexShader* vs, scene::IModel* model);
		int addBuffer(IVertexShader* vs);
	}
}
