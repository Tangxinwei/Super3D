#pragma once
#include <common\SDObject.h>
#include <common\CommonType.h>
#include "D3D11CommonType.h"
#include <math\sdmath.h>
#include "../IBuffer.h"
namespace render
{
	class D3D11Buffer : public IBuffer
	{
	protected:
		ID3D11Buffer* buffer;
	public:
		D3D11Buffer(E_CPU_FLAG ecf, E_BIND_FLAG ebf, uint32_t len, ID3D11Buffer* b) : IBuffer(ecf, ebf, len), buffer(b)
		{

		}
		
		virtual ~D3D11Buffer() 
		{
			SafeRelease(buffer);
		}

		virtual void* getBuffer()
		{
			return buffer;
		}
	};
}

