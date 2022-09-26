#include "VBVector3.h"

VBVector3::VBVector3() : x(0), y(0), z(0)
{
}

VBVector3::VBVector3(float X, float Y, float Z) : x(X), y(Y), z(Z)
{
}

VBVector3 VBVector3::operator=(const VBVector3& rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	x = rhs.x;
	y = rhs.y;
	z = rhs.z;
	return *this;
}

VBVector3 VBVector3::operator+(const VBVector3& rhs)
{
	VBVector3 ret;
	ret.x = this->x + rhs.x;
	ret.y = this->y + rhs.y;
	ret.z = this->z + rhs.z;
	return ret;
}

VBVector3 VBVector3::operator-(const VBVector3& rhs)
{
	VBVector3 ret;
	ret.x = this->x - rhs.x;
	ret.y = this->y - rhs.y;
	ret.z = this->z - rhs.z;
	return ret;
}

glm::vec3 VBVector3::ToGlmVec3()
{
	return glm::vec3(x, y, z);
}
