#pragma once

#include <math\sdmath.h>
using namespace sdmath;
#include <common\CommonType.h>
#include "IVertexShader.h"
namespace render
{
	class SimpleVertex
	{
	public:
		vec3 position;
		vec4 color;
		SimpleVertex(vec3& p, vec4& c) : position(p), color(c){}
		SimpleVertex interpolate(const SimpleVertex& sv, const float d)
		{
			return SimpleVertex(sdmath::interpolate(position, sv.position, d), \
				sdmath::interpolate(color, sv.color, d));
		}
	};
	class SD3DVertex
	{
	public:
		vec3 position;
		vec3 normal;
		vec4 color;
		vec2 coords;

		SD3DVertex() {}
		SD3DVertex(float x, float y, float z, float nx, float ny, float nz, vec4& c, float u, float v) :\
			position(x, y, z), normal(nx, ny, nz), color(c), coords(u, v) {}
		SD3DVertex(vec3& p, vec3& n, vec4& c, vec2& co) :position(p), normal(n), color(c), coords(co) {}

		SD3DVertex interpolate(const SD3DVertex& sv, const float d)
		{
			return SD3DVertex(sdmath::interpolate(position, sv.position, d), \
				sdmath::interpolate(normal, sv.normal, d), sdmath::interpolate(color, sv.color, d), \
				sdmath::interpolate(coords, sv.coords, d));
		}
	};

	uint32_t getVertexSizeByType(E_VERTEX_TYPE vt);
}