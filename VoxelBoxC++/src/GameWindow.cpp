#include "GameWindow.h"
#include <iostream>

void frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GameWindow::GameWindow()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "VoxelBox C++", NULL, NULL);

	if (!window)
	{
		std::cout << "Failed to create window\n";
		return;
	}
	windowSuccess = true;

	glfwMakeContextCurrent(window);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, frame_buffer_size_callback);

	glfwMaximizeWindow(window);

}

GameWindow::~GameWindow()
{
}

GLFWwindow* GameWindow::GetWindow()
{
	return window;
}

bool GameWindow::GetWindowSuccess()
{
	return windowSuccess;
}
