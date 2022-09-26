#include "FlyCamera.h"

FlyCamera::FlyCamera(GLFWwindow* window, glm::vec3 position)
	: cameraPosition(position), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(0.0f, 1.0f, 0.0f), camYaw(-90.0f), camPitch(0.0f),
	lastX(0.0f), lastY(0.0f), firstMouse(true), cameraSensitivity(CAM_SENSITIVITY), cursorDisabled(true), sprint(false), 
	ray(VBVector3(position.x, position.y, position.z), 10, camPitch, camYaw)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
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

void FlyCamera::CastRay()
{
	//sudo code for DDA in 3D
	//In order for this to work two planes need to be evaluated
	//The steps will be derrived from the X/Y plane and the X/Z plane
	//because it is easier to derrive them from seperate 2D planes instead
	//of a single 3D environment

	//Calculate step size
	// xRayStep = sqrt(1 + (rayDir.y / rayDir.x)^2)
	// yRayStep = sqrt(1 + (rayDir.x / rayDir.y)^2)
	// zRayStep = sqrt(1 + (rayDir.x / rayDir.z)^2)

	//Variables to track data as ray is cast
	//Keep track of the block we are in in global world space (VBVector3)
	//Keep track of the ray length in the x, y, and z component (float)
	//Keep track of the step direction for the x, y, and z direction (int)

	//Ray starting conditions
	//X axis
	//	if(rayDir.x < 0)
	//		stepXDir = -1
	//		rayLength = (how much the x component is in the block) * stepX
	//	else
	//		stepXDir = 1
	//		rayLength = (how much the ray travels before exiting the block) * stepX
	//	endIf

	//Y axis
	//	if(rayDir.y < 0)
	//		stepYDir = -1
	//		rayLength = (how much the y component is in the block) * stepY
	//	else
	//		stepYDir = 1
	//		rayLength = (how much the ray travels before exiting the block) * stepY
	//	endIf

	//Z axis
	//	if(rayDir.z < 0)
	//		stepZDir = -1
	//		rayLength = (how much the z component is in the block) * stepZ
	//	else
	//		stepZDir = 1
	//		rayLength = (how much the ray travels before exiting the block) * stepZ
	//	endIf

	//Perform the DDA algorithm
	//	while (!blockFound || currentDist < maxDist)
	//		if(xRayLen < yRayLen && xRayLen < zRayLen)
	//			currentBlock += stepXDir
	//			currentDist = xRayLen
	//			xRayLen += xRayStep;
	//		else if(yRayLen < xRayLen && yRayLen < zRayLen)
	//			currentBlock += stepYDir
	//			currentDist = yRayLen
	//			yRayLen += yRayStep
	//		else if(zRayLen < xRayLen && zRayLen < yRayLen)
	//			currentBlock += stepZDir
	//			currentDist = zRayLen
	//			zRayLen += zRayStep
	//		endIf
	// 
	//		Convert global coord into local chunk coord
	//		If that block is not air do something
	// 
	//	endWhile
}
