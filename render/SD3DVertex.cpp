#include "SD3DVertex.h"

namespace render
{
	uint32_t getVertexSizeByType(E_VERTEX_TYPE vt)
	{
		switch (vt)
		{
		case EVT_STANDARD:
			return sizeof(SD3DVertex);
		}
		return 0;
	}
}