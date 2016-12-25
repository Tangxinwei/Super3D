#include "ShaderDefs.h"

namespace render
{
	InputLayout SimpleVertexHLSL::VS_INPUT_LAYOUT::input[] = {
		{ "POSITION", 0, GI_FORMAT_R32G32B32_FLOAT, 0, 0 },
		{ "COLOR", 0,GI_FORMAT_R32G32B32_FLOAT, 0, 12 },
	};
}