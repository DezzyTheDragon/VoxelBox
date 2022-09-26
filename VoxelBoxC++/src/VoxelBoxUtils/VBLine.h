#pragma once
#include "VBVector3.h"

class VBLine
{
	unsigned int VAO = 0;
	unsigned int VBO = 0;
public:
	~VBLine();
	void DrawLine(VBVector3 p1, VBVector3 p2);

};