#include "FlyCamera.h"


#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <string>
#include <iostream>
#include "VoxelBoxCallbacks.h"

void FlyCamera::handleInput()
{
	if (cameraBind.testButton == true)
	{
		cameraBind.testButton = false;
	}
	if (cameraBind.leftClick == true)
	{
		breakBlock();
		cameraBind.leftClick = false;
	}
	if (cameraBind.rightClick == true)
	{
		placeBlock();
		cameraBind.rightClick = false;
	}
}

void FlyCamera::breakBlock()
{
	CastRay(1);
}

void FlyCamera::placeBlock()
{
	if (blockInRange)
	{
		std::cout << "Placing block\n";
	}
}

void FlyCamera::CastRay(int actionType)
{
	//sudo code for DDA in 3D
	//In order for this to work two planes need to be evaluated
	//The steps will be derrived from the X/Y plane and the X/Z plane
	//because it is easier to derrive them from seperate 2D planes instead
	//of a single 3D environment


	//float xRayUnitStep = sqrt(1 + ((ray.direction.z / ray.direction.x) * (ray.direction.z / ray.direction.x)));
	//float yRayUnitStep = sqrt(1 + ((ray.direction.x / ray.direction.y) * (ray.direction.x / ray.direction.y)));
	//float zRayUnitStep = sqrt(1 + ((ray.direction.x / ray.direction.z) * (ray.direction.x / ray.direction.z)));

	float xRayUnitStep = abs(1 / ray.direction.x);
	float yRayUnitStep = abs(1 / ray.direction.y);
	float zRayUnitStep = abs(1 / ray.direction.z);


	int xWorldRayPos = (int)ray.origin.x;
	int yWorldRayPos = (int)ray.origin.y;
	int zWorldRayPos = (int)ray.origin.z;
	float xRayLength = 0.0f;
	float yRayLength = 0.0f;
	float zRayLength = 0.0f;
	int xStepDir = 0;
	int yStepDir = 0;
	int zStepDir = 0;


	if (ray.direction.x < 0)
	{
		xStepDir = -1;
		xRayLength = (ray.origin.x - float(xWorldRayPos)) * xRayUnitStep;
	}
	else
	{
		xStepDir = 1;
		xRayLength = ((float(xWorldRayPos) + 1) - ray.origin.x) * xRayUnitStep;
	}


	if (ray.direction.y < 0)
	{
		yStepDir = -1;
		yRayLength = (ray.origin.y - float(yWorldRayPos)) * yRayUnitStep;
	}
	else
	{
		yStepDir = 1;
		yRayLength = ((float(yWorldRayPos) + 1) - ray.origin.y) * yRayUnitStep;
	}


	if (ray.direction.z < 0)
	{
		zStepDir = -1;
		zRayLength = (ray.origin.z - float(zWorldRayPos)) * zRayUnitStep;
	}
	else
	{
		zStepDir = 1;
		zRayLength = ((float(zWorldRayPos) + 1) - ray.origin.z) * zRayUnitStep;
	}

	bool blockFound = false;
	float currentDist = 0.0f;
	int block = -1;
	int chunkCoordX = 0;
	int chunkCoordY = 0;
	int localChunkCoordX = 0;
	int localChunkCoordY = 0;

	while (!blockFound && currentDist < ray.maxDistance)
	{
		if (xRayLength < yRayLength)
		{
			if (xRayLength < zRayLength)
			{
				xWorldRayPos += xStepDir;
				currentDist = xRayLength;
				xRayLength += xRayUnitStep;
			}
			else
			{
				zWorldRayPos += xStepDir;
				currentDist = zRayLength;
				zRayLength += zRayUnitStep;
			}
		}
		else
		{
			if (yRayLength < zRayLength)
			{
				yWorldRayPos += yStepDir;
				currentDist = yRayLength;
				yRayLength += yRayUnitStep;
			}
			else
			{
				zWorldRayPos += xStepDir;
				currentDist = zRayLength;
				zRayLength += zRayUnitStep;
			}
		}


		if (xWorldRayPos > -1)
		{
			localChunkCoordX = xWorldRayPos % 16;
			chunkCoordX = xWorldRayPos / 16;
		}
		else
		{
			localChunkCoordX = (xWorldRayPos + 16) % 16;
			chunkCoordX = (xWorldRayPos - 16) / 16;
		}
		if (zWorldRayPos > -1)
		{
			localChunkCoordY = zWorldRayPos % 16;
			chunkCoordY = xWorldRayPos / 16;
		}
		else
		{
			localChunkCoordY = (zWorldRayPos + 16) % 16;
			chunkCoordY = (zWorldRayPos - 16) / 16;
		}

		std::map<std::pair<int, int>, WorldChunkData*>::iterator it = worldData->find(std::pair<int, int>(chunkCoordX, chunkCoordY));
		if (it->second->chunkData[localChunkCoordX][localChunkCoordY][yWorldRayPos] != 0)
		{
			blockFound = true;
			blockInRange = true;
			
			if (actionType == 1)
			{
				//Break block
				std::cout << "Breaking block\n";
				it->second->chunkData[localChunkCoordX][localChunkCoordY][yWorldRayPos] = 0;
				it->second->chunkDirty = true;
			}
			else if (actionType == 2)
			{
				//Place block
			}
			block = it->second->chunkData[localChunkCoordX][localChunkCoordY][yWorldRayPos];
		}
		else
		{
			blockInRange = false;
		}
	}

	//ImGUI for testing purposes
	/*
	ImGui::Begin("RayCast");
	ImGui::SetWindowSize(ImVec2(0, 0));
	ImGui::Text("Ray Dir: %.3f, %.3f, %.3f", ray.direction.x, ray.direction.y, ray.direction.z);
	ImGui::Text("Ray Step Dir: %d, %d, %d", xStepDir, yStepDir, zStepDir);
	ImGui::Text("Ray Unit Step: %.3f, %.3f, %.3f", xRayUnitStep, yRayUnitStep, zRayUnitStep);
	ImGui::Text("Ray Length: %.3f, %.3f, %.3f", xRayLength, yRayLength, zRayLength);
	ImGui::Text("World Ray Pos: %d, %d, %d", xWorldRayPos, yWorldRayPos, zWorldRayPos);
	ImGui::Text("Chunk Coord: %d, %d", chunkCoordX, chunkCoordY);
	ImGui::Text("Block Coord: %d, %d, %d", localChunkCoordX, yWorldRayPos, localChunkCoordY);
	ImGui::Text("Block: %d", block);
	ImGui::End();
	*/
}

FlyCamera::FlyCamera(GLFWwindow* window, glm::vec3 position)
	: cameraPosition(position), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(0.0f, 1.0f, 0.0f), camYaw(-90.0f), camPitch(0.1f),
	lastX(0.0f), lastY(0.0f), firstMouse(true), cameraSensitivity(CAM_SENSITIVITY), cursorDisabled(true), sprint(false), 
	ray(VBVector3(position.x, position.y, position.z), 3, camPitch, camYaw)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(window, cameraKeyTestCallback);
	glfwSetMouseButtonCallback(window, cameraMouseButtonTestCallback);
}

//Keyboard input to move camera position
void FlyCamera::CameraKeyboardInput(GLFWwindow* window, float deltaTime)
{
	float cameraSpeed = CAM_SPEED * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		cameraSpeed *= 3;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPosition += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPosition -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}

	ray.UpdateOrigin(VBVector3(cameraPosition.x, cameraPosition.y, cameraPosition.z));

	//Enable the cursor
	if (glfwGetKey(window, GLFW_KEY_GRAVE_ACCENT) == GLFW_PRESS && cursorDisabled)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		cursorDisabled = false;
		firstMouse = true;
	}

	
}

void FlyCamera::CameraMouseInput(float xpos, float ypos)
{
	if (cursorDisabled)
	{
		if (firstMouse)
		{
			firstMouse = false;
			lastX = xpos;
			lastY = ypos;
		}

		float offsetX = xpos - lastX;
		float offsetY = lastY - ypos;
		lastX = xpos;
		lastY = ypos;

		offsetX *= cameraSensitivity;
		offsetY *= cameraSensitivity;

		camYaw += offsetX;
		camPitch += offsetY;

		//Limit the pitch to avoid unusual camera rotations
		//limited at 89 degrees because it causes AtLook to 
		//flip if the pitch is equal to world up
		if (camPitch > 89.0f)
		{
			camPitch = 89.0f;
		}
		if (camPitch < -89.0f)
		{
			camPitch = -89.0f;
		}

		ray.UpdateRotation(camPitch, camYaw);

		glm::vec3 direction;
		direction.x = cos(glm::radians(camYaw)) * cos(glm::radians(camPitch));
		direction.y = sin(glm::radians(camPitch));
		direction.z = sin(glm::radians(camYaw)) * cos(glm::radians(camPitch));
		cameraFront = glm::normalize(direction);
	}
}

void FlyCamera::ResumeCamera(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	cursorDisabled = true;
}

glm::mat4 FlyCamera::GetFlyCameraView()
{
	return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

glm::vec3 FlyCamera::GetCameraPosition()
{
	return cameraPosition;
}

glm::vec2 FlyCamera::GetCameraRotation()
{
	return glm::vec2(camPitch, camYaw);
}

void FlyCamera::setWorldDataReference(std::map<std::pair<int, int>, WorldChunkData*>* worldDat)
{
	worldData = worldDat;
}



void FlyCamera::Update()
{
	handleInput();
}

