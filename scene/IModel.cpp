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
}