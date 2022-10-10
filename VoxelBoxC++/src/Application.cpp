#pragma once
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <stdlib.h>
#include <crtdbg.h>

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif // !GLEW_STATIC


#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "stb_image.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "GameWindow.h"
#include "HandleInput.h"
#include "Shader.h"
#include "FlyCamera.h"
#include "DrawChunk.h"
#include "LoadChunk.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

//TODO: Move the window to be a global variable

//TODO: Currently global variable only for mouse_callback
//		Figure out how to work with and use callbacks so
//		this camera dosn't need to be a global variable
FlyCamera* mainCamera;

void mouse_callback(GLFWwindow *window, double xpos, double ypos);


void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void ImGuiTestWindow(GLFWwindow* window)
{
	glm::vec3 camPos = mainCamera->GetCameraPosition();
	glm::vec2 camRot = mainCamera->GetCameraRotation();
	int localChunkCoordX = 0;
	int localChunkCoordY = 0;
	int chunkCoordX = 0;
	int chunkCoordY = 0;
	if (camPos.x > -1)
	{
		localChunkCoordX = (int)camPos.x % 16;
		chunkCoordX = (int)camPos.x / 16;
	}
	else
	{
		localChunkCoordX = ((int)camPos.x + 16) % 16;
		chunkCoordX = ((int)camPos.x - 16) / 16;
	}
	if (camPos.z > -1)
	{
		localChunkCoordY = (int)camPos.z % 16;
		chunkCoordY = (int)camPos.z / 16;
	}
	else
	{
		localChunkCoordY = ((int)camPos.z + 16) % 16;
		chunkCoordY = ((int)camPos.z - 16) / 16;
	}
	ImGui::Begin("Render Debug");
	ImGui::SetWindowSize(ImVec2(0,0));
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::Text("Controlls");
	ImGui::Text("WASD: move | Left Shift: Speed up");
	ImGui::Text("Escape: quit | Grave: free cursor");
	ImGui::Text("Camera Position: %.2f, %.2f, %.2f", camPos.x, camPos.y, camPos.z);
	ImGui::Text("Chunk Local Coord: %d, %d", localChunkCoordX, localChunkCoordY);
	ImGui::Text("Chunk Coord: %d, %d", chunkCoordX, chunkCoordY);
	if (ImGui::Button("Resume Camera"))
	{
		//std::cout << "Resuming camera\n";
		mainCamera->ResumeCamera(window);
	}
	ImGui::End();
}

void ImGuiMeshData(float* vert, unsigned int* ind, int vertCount, int indCount)
{
	ImGui::Begin("Chunk Mesh Data");
	ImGui::SetWindowSize(ImVec2(300,400));
	ImGui::Text("Chunk Vertecies");
	ImGui::BeginChild("Scroll");
	
	for (int i = 0; i < vertCount / 10; i++)
	{
		
		ImGui::Text("Vert: %.1f, %.1f, %.1f", *(vert + (i * 10)), *(vert + (i * 10) + 1), *(vert + (i * 10) + 2));
	}
	for (int i = 0; i < indCount / 3; i++)
	{
		ImGui::Text("Ind: %d, %d, %d", *(ind + (i * 3)), *(ind + (i * 3) + 1), *(ind + (i * 3) + 2));
	}
	ImGui::EndChild();
	ImGui::End();
}

int main()
{
	//Memory leak dump
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG);

	//init glfw
	//glfw is a opengl window manager system
	if (!glfwInit())
	{
		std::cout << "Failed to create GLFW\n";
		return -1;
	}

	//window reference
	GLFWwindow* win;

	//Create window useing my window class
	GameWindow* gameWin = new GameWindow();
	win = gameWin->GetWindow();

	//Check that the window was created successfully and terminate if it failed
	if (!gameWin->GetWindowSuccess())
	{
		glfwTerminate();
		return -1;
	}
	
	//Init glew
	//openGL is a standard but it dosn't contain functions
	//glew contains functions that can be used
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW\n";
		glfwTerminate();
		return -1;
	}
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	//Get and store window size to use in matricies
	int winWidth;
	int winHeight;
	glfwGetWindowSize(win, &winWidth, &winHeight);

	//Init ImGUI
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(win, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	
	//Create new camera system using my FlyCamera class
	mainCamera = new FlyCamera(win, glm::vec3(0.0f, 5.0f, 0.0f));

	//Hide and lock the cursor into the window
	//glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Set the mouse position callback
	glfwSetCursorPosCallback(win, mouse_callback);


	//This changes things into wire frame mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	Shader chunkShader("BasicBlockShader.vs", "BasicBlockShader.fs");

	LoadChunk* chunkLoader = new LoadChunk(mainCamera);
	mainCamera->setWorldDataReference(&chunkLoader->worldData);

	//projection matrix to change from 3D into 2D that can be displayed on the screen
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)winWidth/(float)winHeight, 0.1f, 100.0f);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	HandleInput input;
	//Program loop, keep running untill
	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
		//Calculate delta time
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		//Input
		//------------------------------------
		//ProcessInput(win);
		input.ProcessInput(win);
		mainCamera->CameraKeyboardInput(win, deltaTime);

		//Render
		//------------------------------------

		glClearColor(0.0f, 0.9f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		chunkLoader->CheckActiveChunks();
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		
		glm::mat4 view;
		view = mainCamera->GetFlyCameraView();

		mainCamera->Update();

		chunkLoader->ShowActiveChunks(view, projection, chunkShader);

		ImGuiTestWindow(win);
		//ImGuiMeshData(chunkTest.GetVertexBuffer(), chunkTest.GetIndicieBuffer(), chunkTest.GetVertexSize(), chunkTest.GetIndicieSize());
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//Swap buffer
		//------------------------------------
		glfwSwapBuffers(win);
	}

	//Kill them all
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	chunkShader.deleteShader();
	delete chunkLoader;
	delete mainCamera;
	delete gameWin;
	glfwTerminate();

	_CrtDumpMemoryLeaks();
	return 0;
}

//Callbacks are confusing
//TODO: figure out a good way to move this call back
//		so that mainCamera dosn't need to be global
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	mainCamera->CameraMouseInput((float)xpos, (float)ypos);
}
