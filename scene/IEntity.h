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
	class IScene;
	class IEntity : public SDObject
	{
	protected:
		sdmath::mat4 transform;
		IScene* pScene;
	public:
		IEntity(): transform(), pScene(NULL){}
		IScene* getCurrentScene() { return pScene; }
		void onAddToScene(IScene* scene){pScene = scene;}
		void setPosition(float x, float y, float z);
		sdmath::mat4 getWorldTransform() { return transform; }
		sdmath::vec3 getPosition();
		virtual void update(float dt) = 0;
		void rotate(sdmath::vec3& axis, float angle);
		void rotateX(float angle) { rotate(sdmath::vec3(1, 0, 0), angle); }
		void rotateY(float angle) { rotate(sdmath::vec3(0, 1, 0), angle); }
		void rotateZ(float angle) { rotate(sdmath::vec3(0, 0, 1), angle); }

		void translate(float x, float y, float z);
		virtual ~IEntity(){}
	}; 
}

