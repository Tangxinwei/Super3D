#pragma once
#include <vector>
#include <util/Function.hpp>
using namespace std;

class SDObject;

class MemPool : public SingletonBase<MemPool>
{
private:
	vector<SDObject*> data;
public:
	void add(SDObject* d) { data.push_back(d); }
	void releaseAll();
};

class SDObject 
{
private:
	int referenceCount;

public:
	virtual ~SDObject() {}
	SDObject():referenceCount(1){}
	void retain() { referenceCount++; }
	bool Release() 
	{
		return release();
	}
	bool release()
	{
		referenceCount--;
		if (referenceCount <= 0)
		{
			delete this;
			return true;
		}
		return false;
	}
	void autoRelease()
	{
		MemPool::getInstance()->add(this);
	}
};
