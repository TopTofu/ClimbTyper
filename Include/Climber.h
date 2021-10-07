#pragma once

#include <Render.h>


struct Climber {
	Mesh mesh;
	Mesh limbMesh;
	std::vector<glm::vec3> limbPos;
	float limbRange = 0.5f;
	float bodyHeight;
	float bodyWidth;
	glm::vec3 initalPos = glm::vec3(0.0f, 0.6f, 0.0f);
};


Climber initClimber(glm::vec3 position);
void renderClimber(Climber& climber, GLuint shader, Camera& camera);
float distance(glm::vec3 a, glm::vec3 b);
void balanceClimberBody(Climber& climber);
glm::vec3 findCenterOfGravity(Climber& climber);
void resetClimberPos(Climber& climber);


