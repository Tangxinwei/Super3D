#include "D3D11Device.h"

namespace render
{
	IDevice* createD3D11Device(CCreationParams& params)
	{
		D3D11Device* device = new D3D11Device();
		if (!device->initDevice(params))
		{
			device->release();
			device = NULL;
		}
		return device;
	}

	bool D3D11Device::initDevice(CCreationParams& params)
	{
		//�����豸
		UINT createDeviceFlags = 0;
		D3D_FEATURE_LEVEL featureLevel;
		if (FAILED(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, 0, createDeviceFlags, \
			0, 0, D3D11_SDK_VERSION, &mpD3dDevice, &featureLevel, &mpImmediateContext)))
		{
			MessageBox(0, L"fail to create device for dx11", 0, 0);
			return false;
		}
		if (featureLevel != D3D_FEATURE_LEVEL_11_0)
		{
			MessageBox(0, L"no support for dx11", 0, 0);
			return false;
		}
		//���һ�¶��ز����ĵȼ�
		mpD3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
		//����swap chain
		DXGI_SWAP_CHAIN_DESC sd;
		memset(&sd, 0, sizeof(sd));
		sd.BufferDesc.Width = params.width;
		sd.BufferDesc.Height = params.height;
		sd.Windowed = !params.fullScreen;
		sd.BufferDesc.RefreshRate.Numerator = 60;
		sd.BufferDesc.RefreshRate.Denominator = 1;
		sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		if (params.enable4xMsaa)
		{
			sd.SampleDesc.Count = 4;
			sd.SampleDesc.Quality = m4xMsaaQuality - 1;
		}
		else
		{
			sd.SampleDesc.Count = 1;
			sd.SampleDesc.Quality = 0;
		}
		sd.OutputWindow = (HWND)params.windowHandler;
		sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		sd.BufferCount = 1;
		sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		//����IXGISwapChainʵ��
		IDXGIDevice *dxgiDevice = 0;
		mpD3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
		IDXGIAdapter *dxgiAdpter = 0;
		dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdpter);
		IDXGIFactory *dxgiFactory = 0;
		HR(dxgiAdpter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));
		HR(dxgiFactory->CreateSwapChain(mpD3dDevice, &sd, &mpSwapChain));
		SafeRelease(dxgiDevice);
		SafeRelease(dxgiAdpter);
		SafeRelease(dxgiFactory);
		onResize(params);
		return true;
	}
	void D3D11Device::onResize(CCreationParams& params)
	{
		SafeRelease(mpRenderTargetView);
		SafeRelease(mpDepthStencilBuffer);
		SafeRelease(mpDepthStencilView);
		//ָ����̨����������ȾĿ����ͼ
		mpSwapChain->ResizeBuffers(1, params.width, params.height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		ID3D11Texture2D* backBuffer;
		mpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		mpD3dDevice->CreateRenderTargetView(backBuffer, 0, &mpRenderTargetView);
		SafeRelease(backBuffer);
		//����ģ�建�����Ȼ���
		D3D11_TEXTURE2D_DESC depthStencilDesc;
		depthStencilDesc.Width = params.width;
		depthStencilDesc.Height = params.height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		if (params.enable4xMsaa)
		{
			depthStencilDesc.SampleDesc.Count = 4;
			depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality - 1;
		}
		else
		{
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
		}
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;
		mpD3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &mpDepthStencilBuffer);
		mpD3dDevice->CreateDepthStencilView(mpDepthStencilBuffer, 0, &mpDepthStencilView);
		mpImmediateContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);
		//�����ӿ�
		mScreenViewport.TopLeftX = 0;
		mScreenViewport.TopLeftY = 0;
		mScreenViewport.Width = params.width;
		mScreenViewport.Height = params.height;
		mScreenViewport.MinDepth = 0;
		mScreenViewport.MaxDepth = 1.0f;
		mpImmediateContext->RSSetViewports(1, &mScreenViewport);
	}

	D3D11Device::~D3D11Device()
	{

	}

	bool D3D11Device::beginScene(bool backBuffer, bool zBuffer, const sdmath::vec4& color)
	{
		if (backBuffer)
		{
			sdmath::vec4 a(0, 0, 0, 1);
			//float a[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			mpImmediateContext->ClearRenderTargetView(mpRenderTargetView, (const float*)&a);
		}
		if (zBuffer)
			mpImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 0, 0);
		return true;
	}
	void D3D11Device::endScene()
	{
		mpSwapChain->Present(0, 0);
	}

	IVertexBuff* D3D11Device::createVertexBuff(int byteLen, void* initData, E_VERTEX_TYPE vType)
	{
		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vertexDesc.ByteWidth = byteLen;
		ID3D11Buffer* pBuff = NULL;
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = initData;
		HRESULT result = mpD3dDevice->CreateBuffer(&vertexDesc, &resourceData, &pBuff);
		HR_RETURN(result);
		return new D3D11VertexBuff(byteLen, pBuff, vType, byteLen / getVertexSizeByType(vType));
	}

	IVertexIndexBuff* D3D11Device::createVertexIndexBuff(int byteLen, void* initData, E_INDEX_TYPE iType)
	{
		D3D11_BUFFER_DESC vertexDesc;
		ZeroMemory(&vertexDesc, sizeof(vertexDesc));
		vertexDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		vertexDesc.ByteWidth = byteLen;
		ID3D11Buffer* pBuff = NULL;
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(resourceData));
		resourceData.pSysMem = initData;
		HRESULT result = mpD3dDevice->CreateBuffer(&vertexDesc, &resourceData, &pBuff);
		HR_RETURN(result);
		uint32_t count = 0;
		switch (iType)
		{
		case EIT_16BIT:
			count = byteLen >> 1;
		}
		return new D3D11VertexIndexBuff(byteLen, pBuff, iType, count);
	}

	void D3D11Device::drawIndexedVertexTriangles(IVertexBuff* pVertex, IVertexIndexBuff* pIndex)
	{
		mpImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		ID3D11Buffer* vertexBuff = (ID3D11Buffer*)pVertex->getBuff();
		UINT stride = getVertexSizeByType(pVertex->getVertexType()), offset = 0;
		mpImmediateContext->IASetVertexBuffers(0, 1, &vertexBuff, &stride, &offset);
		
		ID3D11Buffer* indexBuff = (ID3D11Buffer*)pIndex->getBuff();
		DXGI_FORMAT indexType = DXGI_FORMAT_UNKNOWN;
		switch (pIndex->getIndexType())
		{
		case EIT_16BIT:
			indexType = DXGI_FORMAT_R16_UINT;
		}
		mpImmediateContext->IASetIndexBuffer(indexBuff, indexType, 0);
		mpImmediateContext->DrawIndexed(pIndex->getIndexCount(), 0, 0);
	}
}
