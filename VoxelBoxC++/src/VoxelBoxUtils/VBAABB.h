#pragma once
#include "VBVector3.h"

/// <summary>
/// Axis Aligned Bounding Box is a collision box with
/// faces parallel to world axis
/// </summary>
class VBAABB
{
public:
	VBVector3 min;
	VBVector3 max;
	VBAABB();
	VBAABB(VBVector3 minVec, VBVector3 maxVec);
};