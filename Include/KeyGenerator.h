#pragma once

#include <vector>
#include <deque>
#include <ctime>
#include <glm/gtc/quaternion.hpp>
#include <chrono>
#include <glm/glm.hpp>
#include <iostream>


struct KeyPrompt {
	char key;
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

	float height;
};

struct Chunk {
	std::vector<char> chars = {};
	std::vector<KeyPrompt> prompts = {};
	std::vector<glm::vec3> clickedPrompts = {};
	float heightOffset = 0;
};

Chunk initChunk(int promptCount, float height);
KeyPrompt getRandomKeyPrompt();
float getRandomHorizontalPos(float lastX);
long long getSeed();