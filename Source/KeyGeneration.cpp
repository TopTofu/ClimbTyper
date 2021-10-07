#include "KeyGenerator.h"


long long getSeed() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


std::vector<char> keySet = { 
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


Chunk initChunk(int promptCount, float height) {
	std::vector<char> temp = keySet;
	Chunk c = {};

	float lastX;

	if (c.prompts.size() < 1) {
		lastX = 1;
	}
	else lastX = c.prompts.back().translation.x;

	for (int i = 0; i < promptCount; i++) {
		size_t t = temp.size();
		char k = temp[rand() % temp.size()];
		c.chars.push_back(k);
		auto it = find(temp.begin(), temp.end(), k);
		temp.erase(it);

		KeyPrompt prompt = { k };

		float increase = ((rand() % 16) + 5.0f) / 100.0f; // interval (0.05, 0.2)
		if (c.prompts.size() > 0) {
			prompt.height = c.prompts.back().height + increase;
		}
		else {
			prompt.height = height;
		}

		float newX = getRandomHorizontalPos(lastX);
		lastX = newX;

		prompt.translation += glm::vec3(newX, prompt.height, 0.0f);
		prompt.scale *= glm::vec3(0.2f, 0.2f, 0.2f);

		c.prompts.push_back(prompt);
	}

	c.heightOffset = c.prompts.back().height;

	return c;
}

float getRandomHorizontalPos(float lastX) {
	int swap = rand() % 100;
	float x;

	if (swap > 10) lastX *= -1; // swap sign with a chance of 90%

	if (lastX > 0) x = (rand() % 6 + 2) / 10.0f; // interval (0.2, 0.7)
	else if (lastX < 0) x = (rand() % 6 - 7) / 10.0f; // interval (-0.7, -0.2)
	else {
		std::cout << "LASTX WAS 0\n";
		x = 0.1;
	}

	return x;
}

KeyPrompt getRandomKeyPrompt() {
	KeyPrompt prompt = {};
	prompt.key = keySet[rand() % keySet.size()];
	return prompt;
}

