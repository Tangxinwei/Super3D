#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include "../IPixelShader.h"
#include "D3D11CommonType.h"
namespace render
{
	class D3D11PixelShader : public IPixelShader
	{
	public:
		ID3D11PixelShader* pixelShader;
	public:
		virtual ~D3D11PixelShader()
		{
			SafeRelease(pixelShader);
		}

		D3D11PixelShader(ID3D11PixelShader* p1) : pixelShader(p1)
		{

		}
	};
}

