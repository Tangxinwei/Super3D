#pragma once
#include "../IDevice.h"
#include <math\sdmath.h>
#include <D3D11.h>
#include <DxErr.h> 
#include "D3D11VertexBuff.h"
#ifndef HR
	#define HR(x) {\
		HRESULT hr = (x);\
		if(FAILED(hr))\
		{\
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true);\
		}\
	}
#endif

#ifndef HR_RETURN
#define HR_RETURN(x){\
		HRESULT hr = (x);\
		if(FAILED(hr))\
		{\
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true);\
			return NULL;\
		}\
	}
#endif

namespace render
{
	class D3D11Device : public IDevice
	{
	private:
		UINT m4xMsaaQuality;
		ID3D11Device* mpD3dDevice;
		ID3D11DeviceContext* mpImmediateContext;
		IDXGISwapChain* mpSwapChain;
		ID3D11Texture2D* mpDepthStencilBuffer;
		ID3D11RenderTargetView* mpRenderTargetView;
		ID3D11DepthStencilView* mpDepthStencilView;
		D3D11_VIEWPORT mScreenViewport;
	public:
		D3D11Device(): mpD3dDevice(0), mpImmediateContext(0), mpSwapChain(0), mpDepthStencilBuffer(0), mpRenderTargetView(0),\
			mpDepthStencilView(0){ this->retain(); }
		~D3D11Device();
		virtual void onResize(CCreationParams& params);
		virtual bool initDevice(CCreationParams& params);
		virtual bool beginScene(bool backBuffer = true, bool zBuffer = true, const sdmath::vec4& color = sdmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		virtual void endScene();
		virtual IVertexBuff* createVertexBuff(int byteLen, void* initData);
		virtual void drawVertexPrimitiveList(const void* vertices, uint32_t vertexCount, \
			const void* indexList, uint32_t primCount, E_VERTEX_TYPE vType = EVT_STANDARD, \
			E_PRIMITIVE_TYPE pType = EPT_TRIANGLES, E_INDEX_TYPE iType = EIT_16BIT);
		virtual void draw2D3DVertexPrimitiveList(const void* vertices,
			uint32_t vertexCount, const void* indexList, uint32_t primitiveCount,
			E_VERTEX_TYPE vType, E_PRIMITIVE_TYPE pType,
			E_INDEX_TYPE iType, bool is3D);
	};
}