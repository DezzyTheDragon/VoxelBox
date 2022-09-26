#include "VBAABB.h"

VBAABB::VBAABB() : min(VBVector3(-0.5f, -0.5f, -0.5f)), max(VBVector3(0.5f, 0.5f, 0.5f))
{
}

VBAABB::VBAABB(VBVector3 minVec, VBVector3 maxVec) : min(minVec), max(maxVec)
{
}
