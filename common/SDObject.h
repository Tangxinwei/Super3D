#pragma once

class SDObject 
{
private:
	int referenceCount;

public:
	SDObject():referenceCount(0){}
	void retain() { referenceCount++; }
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