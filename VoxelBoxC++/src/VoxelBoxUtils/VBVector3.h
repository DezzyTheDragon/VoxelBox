#pragma once
#include <GL/glew.h>
#include <glm.hpp>

/// <summary>
/// VoxelBox vector 3 used to store a position in 3D space
/// </summary>
class VBVector3
{
private:
public:
	float x;
	float y;
	float z;
	VBVector3();
	VBVector3(float x, float y, float z);
	VBVector3 operator=(const VBVector3& rhs);
	VBVector3 operator+(const VBVector3& rhs);
	VBVector3 operator-(const VBVector3& rhs);
	/// <summary>
	/// Takes the vector 3 and returns a glm::vec3 used by OpenGL systems
	/// </summary>
	/// <returns>glm::vec3</returns>
	glm::vec3 ToGlmVec3();
	void Normalize();
};