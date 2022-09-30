#ifndef CAMERA
#define CAMERA

#include <Gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <utility>
#include <map>
#include "VoxelBoxStructs.h"
#include "VoxelBoxUtils/VBRay.h"


class FlyCamera
{
private:
	//Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float CAM_SPEED = 2.5f;
	const float CAM_SENSITIVITY = 0.1f;

	//Camera vectors
	glm::vec3 cameraPosition;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	//Camera rotations
	float camYaw;
	float camPitch;

	//Camera controlls
	float lastX;
	float lastY;
	bool firstMouse;
	float cameraSensitivity;
	bool cursorDisabled;
	bool sprint;

	//Ray for interactions
	VBRay ray;
public:

	FlyCamera(GLFWwindow* window, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
	void CameraKeyboardInput(GLFWwindow *window, float deltaTime);
	void CameraMouseInput(float xpos, float ypos);
	void ResumeCamera(GLFWwindow *window);
	glm::mat4 GetFlyCameraView();
	glm::vec3 GetCameraPosition();
	glm::vec2 GetCameraRotation();
	void CastRay(std::map<std::pair<int, int>, WorldChunkData*> worldDat);
};

#endif // !CAMERA
