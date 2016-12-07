#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include <D3D11.h>
#include <DxErr.h> 
#include "../IVertexBuff.h"
namespace render
{
	class D3D11VertexBuff : public IVertexBuff
	{
	protected:
		ID3D11Buffer* pBuff;
	public:
		D3D11VertexBuff(uint32_t len, ID3D11Buffer* b, E_VERTEX_TYPE vType): IVertexBuff(len, vType), pBuff(b){}
		virtual ~D3D11VertexBuff(){ SafeRelease(pBuff); }
	};
}

