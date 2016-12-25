#pragma once
#include <common\CommonType.h>
#include <D3D11.h>
#include <DxErr.h> 
#include <D3DCompiler.h>
#include <D3DX11async.h>

namespace render
{
	inline D3D_PRIMITIVE convertCommonType(E_PRIMITIVE_TYPE ept)
	{
		switch (ept)
		{
		case EPT_TRIANGLES:
			return D3D_PRIMITIVE_TRIANGLE;
		}
		return D3D_PRIMITIVE_TRIANGLE;
	}

	inline DXGI_FORMAT convertCommonType(E_INDEX_TYPE eit)
	{
		switch (eit)
		{
		case EIT_16BIT:
			return DXGI_FORMAT_R16_UINT;
		}
		return DXGI_FORMAT_R16_UINT;
	}

	inline DXGI_FORMAT convertCommonType(E_GIFORMAT_TYPE egt)
	{
		switch (egt)
		{
		case GI_FORMAT_R32G32B32_FLOAT:
			return DXGI_FORMAT_R32G32B32_FLOAT;
		case GI_FORMAT_R32G32_FLOAT:
			return DXGI_FORMAT_R32G32_FLOAT;
		}
		return DXGI_FORMAT_R16_UINT;
	}

	inline D3D11_BIND_FLAG convertCommonType(E_BIND_FLAG ebf)
	{
		switch (ebf)
		{
		case EBF_CONSTANT_BUFFER:
			return D3D11_BIND_CONSTANT_BUFFER;
		}
		return D3D11_BIND_CONSTANT_BUFFER;
	}

	inline D3D11_CPU_ACCESS_FLAG convertCommonType(E_CPU_FLAG ecf)
	{
		switch (ecf)
		{
		case ECF_WRITE:
			return D3D11_CPU_ACCESS_WRITE;
		}
		return D3D11_CPU_ACCESS_WRITE;
	}
}

