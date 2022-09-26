#include "VBRay.h"

void VBRay::calculateDirection(float xRot, float yRot)
{
	float xRotRad = xRot * (3.1415f / 180.0f);
	float yRotRad = yRot * (3.1415f / 180.0f);
	VBVector3 dir;
	dir.x = cos(yRotRad) * cos(xRotRad);
	dir.y = sin(xRotRad);
	dir.z = sin(yRotRad) * cos(xRotRad);
	direction = dir;
}

VBRay::VBRay(VBVector3 origin, float dist) : origin(origin), maxDistance(dist)
{
	calculateDirection(0.0f, 0.0f);
}

VBRay::VBRay(VBVector3 origin, float dist, float xRot, float yRot) : origin(origin), maxDistance(dist)
{
	calculateDirection(xRot, yRot);
}

void VBRay::UpdateRotation(float xRot, float yRot)
{
	calculateDirection(xRot, yRot);
}

void VBRay::UpdateOrigin(VBVector3 origin)
{
	this->origin = origin;
}
