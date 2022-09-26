#pragma once
#include "VBVector3.h"
#include "VBAABB.h"

class VBGameObject
{
private:
protected:
	VBVector3 position;
	VBAABB aabb;
public:
	VBGameObject();
	VBGameObject(VBVector3 pos);
	VBGameObject(VBAABB aabb);
	VBGameObject(VBVector3 pos, VBAABB aabb);
	VBVector3 GetPosition();
	void Transform(VBVector3 newPos);
};