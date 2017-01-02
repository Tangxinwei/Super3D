#pragma once
#include <common\SDObject.h>
#include <common\CommonType.h>
#include <math\sdmath.h>
#include <vector>
#include <util\Function.hpp>

using namespace std;
namespace scene
{
	class IModel;
}
namespace render
{
	class IBuffer;
	struct InputLayout
	{
		const char* semanticName;
		unsigned int semanticIndex;
		E_GIFORMAT_TYPE gi_format;
		unsigned int inputSlot;
		unsigned int inputByteOffset;
	};
	class IVertexShader : public SDObject
	{
	private:
		vector<IBuffer*> bufferList;
		E_SHADER_TYPE shaderType;
	public:
		IVertexShader(E_SHADER_TYPE shaderType);
		virtual ~IVertexShader();
		void addBuffer(IBuffer* buff);
		IBuffer* getBufferByIdx(int idx) { return bufferList[idx]; }
		vector<IBuffer*>& getBufferList() { return bufferList; }
		void setParams(scene::IModel* model);
	};
}

