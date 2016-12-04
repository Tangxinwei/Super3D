#pragma once

#define SafeRelease(x) {if(x){x->Release();x=NULL;}}
#define SafeDelete(x) {if(x){delete x;x=NULL;}}

namespace render 
{
	enum DeviceType { DT_DX11, };
	enum E_VERTEX_TYPE { EVT_STANDARD, };
	enum E_PRIMITIVE_TYPE { EPT_TRIANGLES, };
	enum E_INDEX_TYPE { EIT_16BIT, };
}