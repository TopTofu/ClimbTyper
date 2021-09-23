#include "Font.h"
#include <iostream>



GLuint loadFontFileIntoTexture(const char* path) {
	int x, y, c;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &x, &y, &c, 0);
	if (!data) {
		printf("Failed to load color file: %s\n", path);
		return 0;
	}

	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (c == 4) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else if (c == 3) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else {
		std::cout << "Dont support " << c << " number of channels\n";
		stbi_image_free(data);
		return 0;
	}
	stbi_image_free(data);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}


GLuint bufferKeyQuad(char c) {
	int position = -1;

	if (int(c) >= 97 && int(c) < 123) {
		position = int(c) - 65 - 8 - 24;
	}
	else { position = (int)c - 65; }

	if (position > 25 || position < 0) {
		printf("Character '%c' is not supported", c);
		return 0;
	}

	float correction = 0.015f;

	float gridX = position % 16;
	float gridY = std::floor(position / CELLS_PER_ROW);

	float glyphSizeX = CELL_HEIGHT / BITMAP_HEIGHT;
	float glyphSizeY = CELL_WIDTH / BITMAP_WIDTH;
	
	float x_offset = glyphSizeX + glyphSizeX * gridX * 2;
	float y_offset = 1.0f - glyphSizeY - glyphSizeY * gridY * 2 + correction;


	std::vector<float> vertices = {
		-0.3f, -0.3f,  0.0f,   x_offset - glyphSizeX, y_offset - glyphSizeY,
		 0.3f, -0.3f,  0.0f,   x_offset + glyphSizeX, y_offset - glyphSizeY,
		 0.3f,  0.3f,  0.0f,   x_offset + glyphSizeX, y_offset + glyphSizeY,
		-0.3f,  0.3f,  0.0f,   x_offset - glyphSizeX, y_offset + glyphSizeY
	};


	std::vector<GLuint> indices = {
		0, 1, 2,
		0, 2, 3
	};

	GLuint vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return vao;
}


char getKeyStroke(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
		return 'A';
	}
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		return 'B';
	}
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		return 'C';
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		return 'D';
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		return 'E';
	}
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		return 'F';
	}
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
		return 'G';
	}
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
		return 'H';
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		return 'I';
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		return 'J';
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		return 'K';
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
		return 'L';
	}
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) {
		return 'M';
	}
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		return 'N';
	}
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
		return 'O';
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		return 'P';
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		return 'Q';
	}
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		return 'R';
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		return 'S';
	}
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
		return 'T';
	}
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		return 'U';
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		return 'V';
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		return 'W';
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
		return 'X';
	}
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
		return 'Y';
	}
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
		return 'Z';
	}
	return 0;
}