#include <Wall.h>

#define BUFFERSIZE 20

Wall initWall() {
	std::srand(getSeed());

	Wall wall = {};

	fillKeyBuffer(wall, BUFFERSIZE);

	wall.holdMesh = getCircleMesh(0.05f, 5);
	bufferMesh(wall.holdMesh);

	return wall;
}

std::vector<char> keyset = {
	'A',
	'B',
	'C',
	'D',
	'E',
	'F',
	'G',
	'H',
	'I',
	'J',
	'K',
	'L',
	'M',
	'N',
	'O',
	'P',
	'Q',
	'R',
	'S',
	'T',
	'U',
	'V',
	'W',
	'X',
	'Y',
	'Z',
};


void fillKeyBuffer(Wall& wall, int count) {
	std::vector<char> temp = keyset;

	// remove all keys from set which were previously used
	for (char c : wall.chars) {
		auto it = find(temp.begin(), temp.end(), c);
		if (it != temp.end()) {
			temp.erase(it);
		}
	}

	// get a lastX to alternate left and right
	float lastX;
	if (wall.keyBuffer.size() < 1) {
		lastX = 1.0f;
	}
	else lastX = wall.keyBuffer.back().translation.x;

	// create prompts
	for (int i = 0; i < count; i++) {
		// get random key from set
		KeyPrompt prompt;
		char k = temp[rand() % temp.size()];

		// save key in prompt
		prompt.key = k;

		// delete key from set
		auto it = find(temp.begin(), temp.end(), k);
		if (it != temp.end()) temp.erase(it); 

		// move up from previous prompt by random amount
		float increase = ((rand() % 16) + 5.0f) / 100.0f; // interval (0.05, 0.2)
		if (wall.keyBuffer.size() > 0) {
			prompt.height = wall.keyBuffer.back().height + increase;
		}
		else prompt.height = increase;

		// get a new horizontal position depending on the previous prompt
		float newX = getRandomHorizontalPos(lastX);
		lastX = newX;

		// set translation and scale
		prompt.translation += glm::vec3(newX, prompt.height, 0.0f);
		prompt.scale *= glm::vec3(0.2f, 0.2f, 0.2f);

		// add prompt to keyBuffer
		wall.keyBuffer.push_back(prompt);
		wall.chars.push_back(k);
	}
}


void renderWall(Wall& wall, GLuint shader, std::map<char, GLuint> quadBuffers, GLuint fontTexture, Camera& camera) {
	for (int i = wall.keyBuffer.size() - 1; i >= 0; i--) {
		wall.holdMesh.translation = wall.keyBuffer[i].translation + glm::vec3(0.075f, -0.075f, 0.0f);
		renderMesh(wall.holdMesh, shader, camera);

		renderKeyQuad(shader, wall.keyBuffer[i], fontTexture, quadBuffers[wall.keyBuffer[i].key]);
	}

	for (glm::vec3 pos : wall.clickedPrompts) {
		wall.holdMesh.translation = pos;
		renderMesh(wall.holdMesh, shader, camera);
	}
}


bool processKeyStroke(Wall& wall, Climber& climber, char key, int& score, int& hp) {
	if (key == 0) return false;

	// find key stroke in wall
	auto it = find(wall.chars.begin(), wall.chars.end(), key);
	if (it == wall.chars.end()) {
		hp--;
		return false;
	}

	int index = it - wall.chars.begin();
	KeyPrompt prompt = wall.keyBuffer[index];
	bool limbFound = false;

	glm::vec3 diagonals[] = {
		glm::normalize(glm::vec3(-1.0f, -1.0f, 0.0f)),
		glm::normalize(glm::vec3( 1.0f, -1.0f, 0.0f)),
		glm::normalize(glm::vec3( 1.0f,  1.0f, 0.0f)),
		glm::normalize(glm::vec3(-1.0f,  1.0f, 0.0f)),
	};
	
	glm::vec3 connectionPoints[] = {
		glm::vec3(climber.mesh.translation.x - climber.bodyWidth / 2, climber.mesh.translation.y - climber.bodyHeight / 2, 0.0f),
		glm::vec3(climber.mesh.translation.x + climber.bodyWidth / 2, climber.mesh.translation.y - climber.bodyHeight / 2, 0.0f),
		glm::vec3(climber.mesh.translation.x + climber.bodyWidth / 2, climber.mesh.translation.y + climber.bodyHeight / 2, 0.0f),
		glm::vec3(climber.mesh.translation.x - climber.bodyWidth / 2, climber.mesh.translation.y + climber.bodyHeight / 2, 0.0f),
	};

	for (int i = 0; i < climber.limbPos.size(); i++) {
		glm::vec3 v = connectionPoints[i] - prompt.translation;
		if (glm::length(v) > climber.limbRange) continue;

		float angle = glm::angle(diagonals[i], v) / 3.14159 * 180;
		std::cout << angle << '\n';
		if (angle < 90.0f) {
			limbFound = true;

			climber.limbPos[i] = prompt.translation;
			balanceClimberBody(climber);
			break;
		}
	}

	if (!limbFound) {
		hp--;
		return false;
	}

	// remember position to draw hold
	wall.clickedPrompts.push_back(wall.keyBuffer[index].translation + glm::vec3(0.075f, -0.075f, 0.0f));

	// clear clicked prompt
	wall.chars.erase(it);
	std::vector<KeyPrompt>::iterator itr = wall.keyBuffer.begin() + index;
	wall.keyBuffer.erase(itr);

	// add a new keyPrompt
	fillKeyBuffer(wall, 1);

	score++;
	
	return true;
}


void findStartingPos(Climber& climber, Wall& wall) {
	float reach = climber.limbRange;

	// left leg
	glm::vec3 ref = glm::normalize(glm::vec3(-1.0f, -1.0f, 0.0f));
	glm::vec3 connectionPoint = glm::vec3(climber.mesh.translation.x - climber.bodyWidth / 2, climber.mesh.translation.y - climber.bodyHeight / 2, 0.0f);

	for (KeyPrompt& prompt : wall.keyBuffer) {
		glm::vec3 v = prompt.translation - connectionPoint;

		if (glm::length(v) > reach) continue;

		float angle = glm::angle(ref, v) / 3.14159 * 180;
		if (angle < 90.0f) {
			climber.limbPos[0] = prompt.translation;
			break;
		}
	}

	// right leg
	ref = glm::normalize(glm::vec3(1.0f, -1.0f, 0.0f));
	connectionPoint = glm::vec3(climber.mesh.translation.x + climber.bodyWidth / 2, climber.mesh.translation.y - climber.bodyHeight / 2, 0.0f);

	for (KeyPrompt& prompt : wall.keyBuffer) {
		glm::vec3 temp = prompt.translation - connectionPoint;

		if (glm::length(temp) > reach) {
			continue;
		}

		float angle = glm::angle(ref, temp) / 3.14159 * 180;
		if (angle < 90.0f) {
			climber.limbPos[1] = prompt.translation;
			break;
		}
	}

	// right hand
	ref = glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f));
	connectionPoint = glm::vec3(climber.mesh.translation.x + climber.bodyWidth / 2, climber.mesh.translation.y + climber.bodyHeight / 2, 0.0f);

	for (KeyPrompt& prompt : wall.keyBuffer) {
		glm::vec3 temp = prompt.translation - connectionPoint;

		if (glm::length(temp) > reach) {
			continue;
		}

		float angle = glm::angle(ref, temp) / 3.14159 * 180;
		if (angle < 90.0f) {
			climber.limbPos[2] = prompt.translation;
			break;
		}
	}

	// left hand
	ref = glm::normalize(glm::vec3(-1.0f, 1.0f, 0.0f));
	connectionPoint = glm::vec3(climber.mesh.translation.x - climber.bodyWidth / 2, climber.mesh.translation.y + climber.bodyHeight / 2, 0.0f);

	for (KeyPrompt& prompt : wall.keyBuffer) {
		glm::vec3 temp = prompt.translation - connectionPoint;

		if (glm::length(temp) > reach) {
			continue;
		}

		float angle = glm::angle(ref, temp) / 3.14159 * 180;
		if (angle < 90.0f) {
			climber.limbPos[3] = prompt.translation;
			break;
		}
	}

	balanceClimberBody(climber);
}
