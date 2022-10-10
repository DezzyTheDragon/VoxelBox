#ifndef CALLBACKS
#define CALLBACKS
#pragma once
#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include "VoxelBoxStructs.h"

CameraKeyBindControll cameraBind;

void cameraKeyTestCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		cameraBind.testButton = true;
	}
}

void cameraMouseButtonTestCallback(GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		cameraBind.leftClick = true;
	}
	else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		cameraBind.rightClick = true;
	}
}

#endif // !CALLBACKS
