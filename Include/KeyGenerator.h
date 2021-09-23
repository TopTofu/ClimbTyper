#pragma once

#include <vector>
#include <deque>
#include <ctime>


struct KeyBuffer {
	std::deque<char> queue;
};


KeyBuffer initBuffer(int size);
void fillBuffer(KeyBuffer& buffer, int count);
void processKeyStroke(KeyBuffer& buffer, char key, int& score, int& hp);
char getRandomKey();
std::vector<char> peekKeys(KeyBuffer& buffer, int count);
