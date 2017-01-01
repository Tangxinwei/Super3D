#include "IVertexShader.h"
#ifdef _WINDOWS
	#include <render\D3D11\D3D11Device.h>
#endif // _WINDOWS
#include "IBuffer.h"
#include "ShaderDefs.h"
namespace render
{
	IVertexShader::IVertexShader(E_SHADER_TYPE shaderType)
	{
		this->shaderType = shaderType;
		switch (shaderType)
		{
		case EST_SIMPLE:
			SimpleVertexHLSL::addBuffer(this);
		}
	}
	IVertexShader::~IVertexShader()
	{
		for each (IBuffer* buffer in bufferList)
		{
			SafeRelease(buffer);
		}
		bufferList.clear();
	}
	void IVertexShader::addBuffer(IBuffer* buff)
	{
		buff->retain();
		bufferList.push_back(buff);
	}
	
	void IVertexShader::setParams(scene::IModel* model)
	{
		switch (shaderType)
		{
		case EST_SIMPLE:
			SimpleVertexHLSL::setParams(this, model);
		}
	}
}