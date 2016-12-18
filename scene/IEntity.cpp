#include "IModel.h"
namespace scene
{
	void IEntity::setPosition(float x, float y, float z)
	{
		transform[3][0] = x;
		transform[3][1] = y;
		transform[3][2] = z;
	}

	sdmath::vec3 IEntity::getPosition()
	{
		return sdmath::vec3(transform[3][0], transform[3][1], transform[3][2]);
	}

	void IEntity::rotate(sdmath::vec3& axis, float angle)
	{
		mat4 t = sdmath::rotate(mat4(), angle, axis);
		transform = t * transform;
	}

	void IEntity::translate(float x, float y, float z)
	{
		mat4 t = sdmath::translate(mat4(), vec3(x, y, z));
		transform = t * transform;
	}
}