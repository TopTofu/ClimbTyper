#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <glad/glad.h>
#include <iostream>

#include <KeyGenerator.h>
#include <Render.h>
#include <Climber.h>


struct Wall {
	std::vector<KeyPrompt> keyBuffer;
	std::vector<char> chars;
	Mesh holdMesh;
	std::vector<glm::vec3> clickedPrompts = {};
};


Wall initWall();
void fillKeyBuffer(Wall& wall, int count);
void renderWall(Wall& wall, GLuint shader, std::map<char, GLuint> quadBuffers, GLuint fontTexture, Camera& camera);
bool processKeyStroke(Wall& wall, Climber& climber, char key, int& score, int& hp);
void findStartingPos(Climber& climber, Wall& wall);
