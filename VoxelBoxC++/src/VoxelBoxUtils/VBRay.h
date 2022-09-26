#pragma once
#include "VBVector3.h"

class VBRay
{
private:
	void calculateDirection(float xRot, float yRot);
public:
	VBVector3 origin;
	VBVector3 direction;
	float maxDistance;
	VBRay(VBVector3 origin, float dist);
	VBRay(VBVector3 origin, float dist, float xRot, float yRot);
	void UpdateRotation(float xRot, float yRot);
	void UpdateOrigin(VBVector3 origin);

};