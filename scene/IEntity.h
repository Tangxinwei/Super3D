#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <render\SD3DVertex.h>
#include <math\sdmath.h>
#include <vector>
using namespace render;
using namespace std;
namespace scene
{
	class IEntity : public SDObject
	{
	protected:
		sdmath::mat4 transform;
	public:
		IEntity(): transform(){}
		void setPosition(float x, float y, float z);
		sdmath::mat4 getWorldTransform() { return transform; }
		sdmath::vec3 getPosition();
		void rotate(sdmath::vec3& axis, float angle);
		void rotateX(float angle) { rotate(sdmath::vec3(1, 0, 0), angle); }
		void rotateY(float angle) { rotate(sdmath::vec3(0, 1, 0), angle); }
		void rotateZ(float angle) { rotate(sdmath::vec3(0, 0, 1), angle); }

		void translate(float x, float y, float z);
		virtual ~IEntity(){}
	}; 
}

