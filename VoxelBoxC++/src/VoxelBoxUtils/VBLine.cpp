#include "VBLine.h"
//#include <Gl/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm.hpp>

VBLine::~VBLine()
{

}

void VBLine::DrawLine(VBVector3 p1, VBVector3 p2)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	float vertBuffer[6] = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, vertBuffer, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
}
