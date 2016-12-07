#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include <D3D11.h>
#include <DxErr.h> 
#include "../IVertexIndexBuff.h"
namespace render
{
	class D3D11VertexIndexBuff : public IVertexIndexBuff
	{
	protected:
		ID3D11Buffer* pBuff;
	public:
		D3D11VertexIndexBuff(uint32_t len, ID3D11Buffer* b, E_INDEX_TYPE iType): IVertexIndexBuff(len, iType), pBuff(b){}
		virtual ~D3D11VertexIndexBuff(){ SafeRelease(pBuff); }
	};
}

