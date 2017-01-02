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
		//创建设备
		UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
		createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
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
		//检查一下多重采样的等级
		mpD3dDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality);
		//配置swap chain
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

		//创建IXGISwapChain实例
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
		windowWidth = params.width;
		windowHeight = params.height;
		//指定后台缓冲区的渲染目标视图
		mpSwapChain->ResizeBuffers(1, params.width, params.height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		ID3D11Texture2D* backBuffer;
		mpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		mpD3dDevice->CreateRenderTargetView(backBuffer, 0, &mpRenderTargetView);
		SafeRelease(backBuffer);
		//创建模板缓冲和深度缓冲
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
		HR(mpD3dDevice->CreateTexture2D(&depthStencilDesc, NULL, &mpDepthStencilBuffer));
		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthStencilDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;
		HR(mpD3dDevice->CreateDepthStencilView(mpDepthStencilBuffer, &descDSV, &mpDepthStencilView));
		mpImmediateContext->OMSetRenderTargets(1, &mpRenderTargetView, mpDepthStencilView);
		//设置视口
		mScreenViewport.TopLeftX = 0;
		mScreenViewport.TopLeftY = 0;
		mScreenViewport.Width = params.width;
		mScreenViewport.Height = params.height;
		mScreenViewport.MinDepth = 0;
		mScreenViewport.MaxDepth = 1.0f;
		mpImmediateContext->RSSetViewports(1, &mScreenViewport);

		//设置裁剪模式
		D3D11_RASTERIZER_DESC noCullDesc;
		ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
		noCullDesc.FillMode = D3D11_FILL_SOLID;
		noCullDesc.CullMode = D3D11_CULL_NONE;
		noCullDesc.FrontCounterClockwise = false;
		noCullDesc.DepthClipEnable = true;
		ID3D11RasterizerState * NoCullRS;
		mpD3dDevice->CreateRasterizerState(&noCullDesc, &NoCullRS);
		mpImmediateContext->RSSetState(NoCullRS);
		NoCullRS->Release();
	}

	D3D11Device::~D3D11Device()
	{

	}

	bool D3D11Device::beginScene(bool backBuffer, bool zBuffer, const sdmath::vec4& color)
	{
		if (backBuffer)
		{
			//sdmath::vec4 a(0, 0, 0, 1);
			//float a[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
			mpImmediateContext->ClearRenderTargetView(mpRenderTargetView, (const float*)&color);
		}
		if (zBuffer)
			mpImmediateContext->ClearDepthStencilView(mpDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);
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
		DXGI_FORMAT indexType = convertCommonType(pIndex->getIndexType());
		
		mpImmediateContext->IASetIndexBuffer(indexBuff, indexType, 0);
		mpImmediateContext->DrawIndexed(pIndex->getIndexCount(), 0, 0);
	}

	HRESULT D3D11Device::compileShaderFromFile(const char* fileName, const char* entryName, const char* shaderModel, ID3DBlob** ppBlob)
	{
		HRESULT hr = S_OK;
		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined(DEBUG) || defined(_DEBUG)
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
		ID3DBlob* pErrorBlob;
		hr = D3DX11CompileFromFileA(fileName, NULL, NULL, entryName, shaderModel, dwShaderFlags, 0, \
			NULL, ppBlob, &pErrorBlob, NULL);
		if (FAILED(hr))
		{
			if (pErrorBlob)
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		}
		SafeRelease(pErrorBlob);
		return hr;
	}
	
	IVertexShader* D3D11Device::createVertexShader(const char* fileName, const char* entryName, InputLayout* layout, int elementNumber, E_SHADER_TYPE shaderType)
	{
		ID3DBlob* pVertexShaderBuffer = NULL;
		ID3D11VertexShader* pVertexShader = NULL;
		HRESULT hr = S_FALSE;
		hr = compileShaderFromFile(fileName, entryName, "vs_4_0", &pVertexShaderBuffer);
		HR_RETURN(hr);
		hr = mpD3dDevice->CreateVertexShader(pVertexShaderBuffer->GetBufferPointer(), \
			pVertexShaderBuffer->GetBufferSize(), NULL, &pVertexShader);
		HR_RETURN(hr);
		D3D11_INPUT_ELEMENT_DESC* d3dLayout = new D3D11_INPUT_ELEMENT_DESC[elementNumber];
		for (int i = 0; i < elementNumber; i++)
		{
			d3dLayout[i].SemanticName = layout[i].semanticName;
			d3dLayout[i].SemanticIndex = layout[i].semanticIndex;
			d3dLayout[i].Format = convertCommonType(layout[i].gi_format);
			d3dLayout[i].InputSlot = layout[i].inputSlot;
			d3dLayout[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
			d3dLayout[i].AlignedByteOffset = layout[i].inputByteOffset;
			d3dLayout[i].InstanceDataStepRate = 0;
		}
		ID3D11InputLayout* pVertexLayout11 = NULL;
		mpD3dDevice->CreateInputLayout(d3dLayout, elementNumber, pVertexShaderBuffer->GetBufferPointer(), \
			pVertexShaderBuffer->GetBufferSize(), &pVertexLayout11);
		SafeRelease(pVertexShaderBuffer);
		delete[]d3dLayout;
		return new D3D11VertexShader(pVertexShader, pVertexLayout11, shaderType);
	}

	IPixelShader* D3D11Device::createPixelShader(const char* fileName, const char* entryName)
	{
		ID3DBlob* pPixelShaderBuffer = NULL;
		HRESULT hr = compileShaderFromFile(fileName, entryName, "ps_4_0", &pPixelShaderBuffer);
		HR_RETURN(hr);
		ID3D11PixelShader* pPixelShader = NULL;
		hr = mpD3dDevice->CreatePixelShader(pPixelShaderBuffer->GetBufferPointer(), \
			pPixelShaderBuffer->GetBufferSize(), NULL, &pPixelShader);
		SafeRelease(pPixelShaderBuffer);
		HR_RETURN(hr);
		return new D3D11PixelShader(pPixelShader);
	}

	void D3D11Device::setPSShader(IPixelShader* ps)
	{
		mpImmediateContext->PSSetShader(((D3D11PixelShader*)ps)->pixelShader, NULL, 0);
	}

	void D3D11Device::setVSShader(IVertexShader* vs)
	{
		D3D11VertexShader* nvs = (D3D11VertexShader*)vs;
		mpImmediateContext->VSSetShader(nvs->vertexShader, NULL, 0);
		mpImmediateContext->IASetInputLayout(nvs->inputLayout);
	}

	IBuffer* D3D11Device::createBuffer(E_CPU_FLAG ecf, E_BIND_FLAG ebf, uint32_t len)
	{
		D3D11_BUFFER_DESC desc;
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.BindFlags = convertCommonType(ebf);
		desc.CPUAccessFlags = convertCommonType(ecf);
		desc.MiscFlags = 0;
		desc.ByteWidth = len;
		ID3D11Buffer* result;
		HRESULT hr = mpD3dDevice->CreateBuffer(&desc, NULL, &result);
		HR_RETURN(hr);
		return (IBuffer*)new D3D11Buffer(ecf, ebf, len, result);
	}

	void D3D11Device::setBufferContent(IBuffer* buffer, void* p, uint32_t size)
	{
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		mpImmediateContext->Map((ID3D11Buffer*)buffer->getBuffer(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		memcpy(MappedResource.pData, p, size);
		mpImmediateContext->Unmap((ID3D11Buffer*)buffer->getBuffer(), 0);
	}

	void D3D11Device::vsSetContentBuffers(IVertexShader* vs, vector<IBuffer*>& buffers, int start, int number)
	{
		ID3D11Buffer** p = (ID3D11Buffer**)malloc(number * sizeof(ID3D11Buffer*));
		for (int i = 0; i < number; i++)
			p[i] = (ID3D11Buffer*) (buffers[i]->getBuffer());
		mpImmediateContext->VSSetConstantBuffers(start, number, p);
		free(p);
	}

	sdmath::mat4 D3D11Device::convertMatrixToShaderResourceMatrix(sdmath::mat4& original)
	{
		return original;
	}
}
