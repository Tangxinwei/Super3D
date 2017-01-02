#include "IModel.h"

namespace scene
{
	IModel::~IModel()
	{
		SafeRelease(pVertex);
		SafeRelease(pIndex);
		SafeRelease(pVertexShader);
		SafeRelease(pPixelShader);
		pScene = NULL;
	}

	void IModel::render()
	{
		IDevice* pDevice = getDeviceInstance();
		pDevice->setPSShader(pPixelShader);
		pDevice->setVSShader(pVertexShader);
		pVertexShader->setParams(this);
		pDevice->drawIndexedVertexTriangles(pVertex, pIndex);
	}

	IModel::IModel(IVertexBuff* v, IVertexIndexBuff* pI, IVertexShader* pVS, IPixelShader* pPS) : pVertex(v), pIndex(pI), \
		 pVertexShader(pVS), pPixelShader(pPS)
	{
		pVertex->retain();
		pIndex->retain();
		pVertexShader->retain();
		pPixelShader->retain();
	}
}