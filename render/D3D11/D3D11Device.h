#pragma once
#include "../IDevice.h"
#include <math\sdmath.h>
#include <D3D11.h>
#include <DxErr.h> 
#include <D3DCompiler.h>
#include <D3DX11async.h>
#include "D3D11VertexBuff.h"
#include "D3D11VertexIndexBuff.h"
#include "D3D11PixelShader.h"
#include "D3D11VertexShader.h"
#include "D3D11Buffer.h"
#ifndef HR
	#define HR(x) {\
		if(FAILED((x)))\
		{\
			DXTrace(__FILE__, (DWORD)__LINE__, (x), L#x, true);\
		}\
	}
#endif

#ifndef HR_RETURN
#define HR_RETURN(x){\
		if(FAILED((x)))\
		{\
			DXTrace(__FILE__, (DWORD)__LINE__, (x), L#x, true);\
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
		int windowWidth, windowHeight;
		
		HRESULT compileShaderFromFile(const char* fileName, const char* entryName,const char* shaderModel, ID3DBlob** ppBlob);
	public:
		D3D11Device(): mpD3dDevice(0), mpImmediateContext(0), mpSwapChain(0), mpDepthStencilBuffer(0), mpRenderTargetView(0),\
			mpDepthStencilView(0){ this->retain(); }
		virtual ~D3D11Device();
		virtual void onResize(CCreationParams& params);
		virtual bool initDevice(CCreationParams& params);
		virtual sdmath::vec2 getWindowSize() { return sdmath::vec2(windowWidth, windowHeight); }
		virtual bool beginScene(bool backBuffer = true, bool zBuffer = true, const sdmath::vec4& color = sdmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		virtual void endScene();
		virtual IVertexBuff* createVertexBuff(int byteLen, void* initData, E_VERTEX_TYPE vType);
		virtual IVertexIndexBuff* createVertexIndexBuff(int byteLen, void* initData, E_INDEX_TYPE iType);
		virtual IBuffer* createBuffer(E_CPU_FLAG ecf, E_BIND_FLAG ebf, uint32_t len);
		virtual void setBufferContent(IBuffer* buffer, void* p, uint32_t size);
		virtual void drawIndexedVertexTriangles(IVertexBuff* pVertex, IVertexIndexBuff* pIndex);
		virtual IVertexShader* createVertexShader(const char* fileName, const char* entryName, InputLayout* layout, int elementNumber, E_SHADER_TYPE shaderType);
		virtual IPixelShader* createPixelShader(const char* filename, const char* entryname);
		virtual void setVSShader(IVertexShader* vs);
		virtual void setPSShader(IPixelShader* ps);
		virtual sdmath::mat4 convertMatrixToShaderResourceMatrix(sdmath::mat4& original);
		virtual void vsSetContentBuffers(IVertexShader* vs, vector<IBuffer*>& buffers, int start, int number);
	};
}