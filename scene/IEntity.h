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
		IEntity* parent;
		vector<IEntity*> children;
	public:
		IEntity(): parent(NULL), transform(){}
	};
}

