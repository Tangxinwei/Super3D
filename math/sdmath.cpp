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

}