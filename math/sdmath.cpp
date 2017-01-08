#pragma once

#include "sdmath.h"

namespace sdmath
{
	mat4 transpose(mat4& mat) 
	{
		return glm::transpose(mat); 
	}

	mat4 translate(mat4& mat, vec3& v) 
	{
		return glm::translate(mat, v); 
	}

	mat4 rotate(mat4& mat, float& angle, vec3& axis)
	{
		return glm::rotate(mat, angle, axis); 
	}

	mat4 inverse(mat4& mat) 
	{ 
		return glm::inverse(mat); 
	}

	mat4 perspective(float fov, float aspect, float near, float far)
	{
		mat4 ret(0);
		float halfCot = 1.0 / tan(fov / 2);
		ret[0][0] = halfCot / aspect;
		ret[1][1] = halfCot;
		ret[2][2] = far / (far - near);
		ret[3][2] = far * near / (near - far);
		ret[2][3] = 1.0f;
		return ret;
	}	

	mat4 scale(mat4& mat, vec3& v)
	{
		return glm::scale(mat, v);
	}
}