#pragma once

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
};