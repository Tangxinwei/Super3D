#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include "../IPixelShader.h"

namespace render
{
	class D3D11PixelShader : public IPixelShader
	{
	private:
		ID3D11PixelShader* pBlob;
	public:
		virtual ~D3D11PixelShader()
		{
			SafeRelease(pBlob);
		}

		D3D11PixelShader(ID3D11PixelShader* p1) : pBlob(p1)
		{

		}
	};
}

