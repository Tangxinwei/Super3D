#pragma once

#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>

namespace sdmath
{
	typedef glm::vec2 vec2;
	typedef glm::vec3 vec3;
	typedef glm::vec4 vec4;
	typedef glm::mat4 mat4;
	inline mat4 transpose(mat4& mat);
	inline mat4 translate(mat4& mat, vec3& v);
	inline mat4 rotate(mat4& mat, float& angle, vec3& axis);
	inline mat4 inverse(mat4& mat);

	template<class T>
    inline T interpolate(const T& t1, const T& t2, float d)
	{
		float inv = 1.0 - d;
		return t1 * inv + t2 * d;
	}
}