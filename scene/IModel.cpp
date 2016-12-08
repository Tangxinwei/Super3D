#include "IModel.h"

namespace scene
{
	IModel::~IModel()
	{
		SafeRelease(pVertex);
		SafeRelease(pIndex);
		pScene = NULL;
	}
}