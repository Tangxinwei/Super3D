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
#include <input\IInput.h>
using namespace render;
namespace scene
{
	class IScene;
	class ICamera : public IEntity
	{
	protected:
		float fov, aspect, nearplane, farplane;
	public:
		ICamera(float f, float a, float n, float fa) : fov(f), aspect(a), nearplane(n), farplane(fa)
		{
			
		}
		void update()
		{
			InputEventDevice* input = getInputEventDeviceInstance();
			if (input->checkKeyIsDown(DIK_A))
				this->translate(0, 0, 0.1);
		}
		void render()
		{
			
		}
		virtual ~ICamera();

		mat4 getProjectionMatrix()
		{
			return sdmath::perspective(fov, aspect, nearplane, farplane);
		}
	};
}

