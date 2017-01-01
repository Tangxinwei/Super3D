#include "SDObject.h"

void MemPool::releaseAll()
{
	for each(SDObject* d in data)
	{
		d->Release();
	}
}