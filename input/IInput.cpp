#include "IInput.h"
#ifdef _WINDOWS
	#include "D3D11\DirectXInput.h"
#endif
InputEventDevice* inputEventDevice = NULL;

void createInputEventDevice(render::DeviceType dt)
{
	switch (dt)
	{
	case render::DT_DX11:
		inputEventDevice = new DirectXInputEventDevice;
	}
}

InputEventDevice* getInputEventDeviceInstance()
{
	return inputEventDevice;
}
