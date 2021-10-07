#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "../Source/Variables.cpp"

struct Camera {
	glm::vec3 position;
	glm::vec3 orientation;
	glm::vec3 up;

	int width;
	int height;
};

Camera initCamera(glm::vec3 position);
glm::mat4 getViewMatrix(Camera& camera);
glm::mat4 getProjectionMatrix(int height, int width);
glm::mat4 getCameraMatrix(Camera& camera);