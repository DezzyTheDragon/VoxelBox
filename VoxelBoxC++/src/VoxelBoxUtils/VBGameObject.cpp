#include "VBGameObject.h"

VBGameObject::VBGameObject()
{
}

VBGameObject::VBGameObject(VBVector3 pos) : position(pos)
{
}

VBGameObject::VBGameObject(VBAABB aabb) : aabb(aabb)
{
}

VBGameObject::VBGameObject(VBVector3 pos, VBAABB aabb) : position(pos), aabb(aabb)
{	
}

VBVector3 VBGameObject::GetPosition()
{
	return position;
}

void VBGameObject::Transform(VBVector3 newPos)
{
	position = newPos;
}


