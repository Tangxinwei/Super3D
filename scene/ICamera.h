#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <render\IDevice.h>
#include <math\sdmath.h>
#include <render\SD3DVertex.h>
#include <render\IVertexShader.h>
#include <render\IPixelShader.h>
#include "IEntity.h"
using namespace render;
namespace scene
{
	class IScene;
	class ICamera : public IEntity
	{
	protected:
		IScene* pScene;
		float fov, aspect, near, far;
	public:
		ICamera(float f, float a, float n, float fa) : fov(f), aspect(a), near(n), far(fa)
		{
			
		}
		void render(IDevice* pDevice)
		{
			
		}
		IScene* getCurrentScene() { return pScene; }
		void onAddToScene(IScene* scene)
		{
			pScene = scene;
		}
		virtual ~ICamera();

		mat4 getProjectionMatrix()
		{
			return sdmath::perspective(fov, aspect, near, far);
		}
	};
}

