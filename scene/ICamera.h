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
		virtual void update(float dt)
		{

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

	class MoveCamera : public ICamera
	{
	private:
		float moveSpeed;
	public:
		MoveCamera(float speed, float f, float a, float n, float fa): ICamera(f, a, n, fa),  moveSpeed(speed) {}
		virtual void update(float dt)
		{
			InputEventDevice* input = getInputEventDeviceInstance();
			float dx = 0, dz = 0, dm = dt * moveSpeed;
			if (input->checkKeyIsDown(DIK_A))
				dx += dm;
			if (input->checkKeyIsDown(DIK_D))
				dx -= dm;
			if (input->checkKeyIsDown(DIK_W))
				dz += dm;
			if (input->checkKeyIsDown(DIK_S))
				dz -= dm;
			vec3 forward = get_z_axis(this->getWorldTransform()), right = get_x_axis(this->getWorldTransform());
			forward = dx * right + dz * forward;
			this->translate(forward.x, forward.y, forward.z);
		}
	};
}

