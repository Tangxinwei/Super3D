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
		mat4:  
			col_type value[4]
			value[0] value[1] value[2] value[3]

			v[0][0]  v[1][0]  v[2][0]  v[3][0]
			v[0][1]  v[1][1]  v[2][1]  v[3][1]
			v[0][2]  v[1][2]  v[2][2]  v[3][2]
			v[0][3]  v[1][3]  v[2][3]  v[3][3]
		vec4 is a row vector
		so vec4 t * mat4 m = (t*v[0], t*v[1], t*v[2], t*v[3])

		but in memery, it saved as the transpose of mat as below
		    v[0][0]  v[0][1]  v[0][2]  v[0][3]
		    v[1][0]  v[1][1]  v[1][2]  v[1][3]
		    v[2][0]  v[2][1]  v[2][2]  v[2][3]
		    v[3][0]  v[3][1]  v[3][2]  v[3][3]
	*/
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