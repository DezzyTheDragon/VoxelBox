#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void frame_buffer_size_callback(GLFWwindow* window, int width, int height);

class GameWindow
{
private:
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 500;
	bool windowSuccess = false;
public:
	GLFWwindow* window;
	GameWindow();
	~GameWindow();
	GLFWwindow* GetWindow();
	bool GetWindowSuccess();
};

