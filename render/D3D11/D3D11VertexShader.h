#pragma once
#include <common\CCreationParams.h>
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include "../IVertexShader.h"

namespace render
{
	class IDevice;
	class D3D11VertexShader : public IVertexShader
	{
	public:
		ID3D11VertexShader* vertexShader;
		ID3D11InputLayout* inputLayout;

	public:
		virtual ~D3D11VertexShader()
		{
			SafeRelease(vertexShader);
			SafeRelease(inputLayout);
		}
		D3D11VertexShader(ID3D11VertexShader* v, ID3D11InputLayout* input, E_SHADER_TYPE shaderType) : \
			vertexShader(v), inputLayout(input), IVertexShader(shaderType){}
	};
}

