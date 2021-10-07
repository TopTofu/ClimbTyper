#include <Climber.h>


Climber initClimber(glm::vec3 position) {
	Climber climber = {};

	climber.mesh = getQuadMesh(0.0f, 0.0f, 0.4f, 0.6f);
	climber.bodyHeight = 0.6f;
	climber.bodyWidth = 0.4f;
	climber.mesh.translation = position;
	bufferMesh(climber.mesh);

	climber.initalPos = position;

	climber.limbPos = { glm::vec3(), glm::vec3(), glm::vec3(), glm::vec3() };
	climber.limbMesh = getCircleMesh(0.06f, 20);
	bufferMesh(climber.limbMesh);

	return climber;
}


void renderClimber(Climber& climber, GLuint shader, Camera& camera) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	renderMesh(climber.mesh, shader, camera);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	for (glm::vec3 pos : climber.limbPos) {
		climber.limbMesh.translation = pos + glm::vec3(0.075f, -0.075f, 0.0f);
		renderMesh(climber.limbMesh, shader, camera);
	}
}


float distance(glm::vec3 a, glm::vec3 b) {
	float x = a.x - b.x;
	float y = a.y - b.y;
	float z = a.z - b.z;
	float d = sqrt(x * x + y * y + z * z);
	return d;
}





void resetClimberPos(Climber& climber) {
	climber.mesh.translation = climber.initalPos;
}


void balanceClimberBody(Climber& climber) {
	glm::vec3 center = findCenterOfGravity(climber);
	climber.mesh.translation = center;

	// angle to be parallel to hands
	glm::vec3 a = climber.limbPos[3];
	glm::vec3 b = climber.limbPos[2];
	glm::vec3 c = glm::vec3(b.x, a.y, 0.0f);

	float acath = glm::length(c - a);
	float hypot = glm::length(b - a);

	float angleArms = glm::acos(acath / hypot);
	
	if (c.y > b.y) angleArms *= -1.0f; // reverse angle if neccessary


	// angle to be parallel to feet
	a = climber.limbPos[1];
	b = climber.limbPos[0];
	c = glm::vec3(b.x, a.y, 0.0f);

	acath = glm::length(c - a);
	hypot = glm::length(b - a);

	float angleFeet = glm::acos(acath / hypot);

	if (c.y > b.y) angleFeet *= -1.0f; // reverse angle if neccessary

	float average = angleArms + angleFeet / 2.0f;

	climber.mesh.rotation = glm::rotate(glm::quat(1.0f, 0.0f, 0.0f, 0.0f), average, glm::vec3(0.0f, 0.0f, 1.0f));
}

glm::vec3 findCenterOfGravity(Climber& climber) {
	glm::vec3 diagonalA = climber.limbPos[2] - climber.limbPos[0];
	glm::vec3 diagonalB = climber.limbPos[3] - climber.limbPos[1];

	glm::vec3 diagonalCenterA = climber.limbPos[0] + diagonalA / 2.0f;
	glm::vec3 diagonalCenterB = climber.limbPos[1] + diagonalB / 2.0f;

	glm::vec3 center = (diagonalCenterB - diagonalCenterA) / 2.0f + diagonalCenterA;

	return center;
}