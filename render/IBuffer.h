#pragma once
#include <common\CommonType.h>
#include <common\SDObject.h>
#include <math\sdmath.h>
namespace render
{
	class IBuffer : public SDObject
	{
	protected:
		uint32_t byteWidth;
	public:
		IBuffer(E_CPU_FLAG ecf, E_BIND_FLAG ebf, uint32_t len) : byteWidth(len) {}
		virtual void* getBuffer() = 0;
		virtual ~IBuffer() {}
	};
}

