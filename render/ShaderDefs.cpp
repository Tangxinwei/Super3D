#include "ShaderDefs.h"
#include <scene\IScene.h>
#include "IDevice.h"
namespace render
{
	namespace SimpleVertexHLSL
	{
		InputLayout VS_INPUT_LAYOUT::input[] = {
			{ "POSITION", 0, GI_FORMAT_R32G32B32A32_FLOAT, 0, 0 },
			{ "COLOR", 0,GI_FORMAT_R32G32B32A32_FLOAT, 0, 16 },
		};

		int setParams(IVertexShader* vs, scene::IModel* model)
		{
			cbPerObject object;
			IDevice* device = getDeviceInstance();
			object.g_world = device->convertMatrixToShaderResourceMatrix(model->getWorldTransform());
			if (model->getCurrentScene())
				object.g_worldViewPorjection = device->convertMatrixToShaderResourceMatrix(\
						model->getCurrentScene()->g_viewProjectionMatrix * model->getWorldTransform());
			device->setBufferContent(vs->getBufferByIdx(0), &object, sizeof(object));
			return 0;
		}

		int addBuffer(IVertexShader* vs)
		{
			IDevice* device = getDeviceInstance();
			IBuffer* buffer = device->createBuffer(E_CPU_FLAG::ECF_WRITE, E_BIND_FLAG::EBF_CONSTANT_BUFFER, sizeof(cbPerObject));
			vs->addBuffer(buffer);
			buffer->release();
			device->vsSetContentBuffers(vs, vs->getBufferList(), 0, 1);
			return 0;
		}
	}
}