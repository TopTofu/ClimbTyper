#include "Camera.h"
#include "Variables.cpp"


Camera initCamera(glm::vec3 position) {
	Camera camera = Camera();
	camera.position = position;
	camera.orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	camera.up = glm::vec3(0.0f, 1.0f, 0.0f);

	camera.width = WINDOW_WIDTH;
	camera.height = WINDOW_HEIGHT;

	return camera;
}

glm::mat4 getViewMatrix(Camera& camera) {
	return glm::lookAt(camera.position, camera.position + camera.orientation, camera.up);
}

glm::mat4 getProjectionMatrix(int width, int height) {
	return glm::perspective(glm::radians(CAMERA_FOV), (float)width / (float)height, 0.1f, 100.0f);
}

glm::mat4 getCameraMatrix(Camera& camera) {
	return getProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT) * getViewMatrix(camera);
}