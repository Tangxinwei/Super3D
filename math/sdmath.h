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
	/*
		vector is a row vector,
		for the mat4, you can use mat4[i] to get the ith col vector
		mat[3] is the translation vector
		in memery, a mat 4 is restored by col vector

		B * A * v means the vector v first transform by matrix A, and then B
		be careful of that A * v does not equals with v * A, we should use A * v all the time

		use B to note for the translate transform of vector v, and then
		C = translate(A, v) equals with C = A * B

		we use right-hand coordinate system
	*/
	mat4 transpose(mat4& mat);
	mat4 translate(mat4& mat, vec3& v);
	mat4 rotate(mat4& mat, float& angle, vec3& axis);
	mat4 inverse(mat4& mat);

	template<class T>
    inline T interpolate(const T& t1, const T& t2, float d)
	{
		float inv = 1.0 - d;
		return t1 * inv + t2 * d;
	}
}