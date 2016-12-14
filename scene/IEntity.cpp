#include "IModel.h"
namespace scene
{
	void IEntity::setPosition(float x, float y, float z)
	{
		transform[0][3] = x;
		transform[1][3] = y;
		transform[2][3] = z;
	}

	sdmath::vec3 IEntity::getPosition()
	{
		return sdmath::vec3(transform[0][3], transform[1][3], transform[2][3]);
	}

	void IEntity::rotate(sdmath::vec3& axis, float angle)
	{
		transform = sdmath::rotate(transform, angle, axis);
	}

	void IEntity::translate(float x, float y, float z)
	{
		transform[0][3] += x;
		transform[1][3] += y;
		transform[2][3] += z;
	}
}