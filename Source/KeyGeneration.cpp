#include "KeyGenerator.h"

KeyBuffer initBuffer(int size) {
	std::srand(std::time(0));
	KeyBuffer b = KeyBuffer();
	fillBuffer(b, size);
	return b;
}


void fillBuffer(KeyBuffer& buffer, int count) {
	for (int i = 0; i < count; i++) {
		buffer.queue.push_back(getRandomKey());
	}
}


void processKeyStroke(KeyBuffer& buffer, char key, int& score, int& hp) {
	if (key == 0) return;
	if (buffer.queue[0] != key) {
		hp--;
		return;
	}

	score++;
	
	buffer.queue.pop_front();

	buffer.queue.push_back(getRandomKey());
}


char getRandomKey() {
	return 'A' + rand() % 26;
}


std::vector<char> peekKeys(KeyBuffer& buffer, int count) {
	std::vector<char> keys = {};

	for (int i = 0; i < count; i++) {
		keys.push_back(buffer.queue[i]);
	}

	return keys;
}