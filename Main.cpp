#include <glad/glad.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "KeyGenerator.h"
#include "Window.h"
#include "Render.h"
#include "Font.h"
#include "Shader.h"


int main() {

	GLFWwindow* window = initWindow(1200, 1000);
	initOpenGL(window, 1200, 1000);

	GLuint texture = loadFontFileIntoTexture("E:/ClimbTyper/Resources/fontAtlasBig.png");
	

	GLuint vertex = compileShader("E:/ClimbTyper/Resources/Shader/default.vert");
	GLuint fragment = compileShader("E:/ClimbTyper/Resources/Shader/default.frag");

	GLuint program = createProgram(vertex, fragment);

	glUseProgram(program);
	//glUniform1i(glGetUniformLocation(program, "Texture"), 0);

	std::map<char, GLuint> allKeyQuads = {
		{'A', bufferKeyQuad('A')},
		{'B', bufferKeyQuad('B')},
		{'C', bufferKeyQuad('C')},
		{'D', bufferKeyQuad('D')},
		{'E', bufferKeyQuad('E')},
		{'F', bufferKeyQuad('F')},
		{'G', bufferKeyQuad('G')},
		{'H', bufferKeyQuad('H')},
		{'I', bufferKeyQuad('I')},
		{'J', bufferKeyQuad('J')},
		{'K', bufferKeyQuad('K')},
		{'L', bufferKeyQuad('L')},
		{'M', bufferKeyQuad('M')},
		{'N', bufferKeyQuad('N')},
		{'O', bufferKeyQuad('O')},
		{'P', bufferKeyQuad('P')},
		{'Q', bufferKeyQuad('Q')},
		{'R', bufferKeyQuad('R')},
		{'S', bufferKeyQuad('S')},
		{'T', bufferKeyQuad('T')},
		{'U', bufferKeyQuad('U')},
		{'V', bufferKeyQuad('V')},
		{'W', bufferKeyQuad('W')},
		{'X', bufferKeyQuad('X')},
		{'Y', bufferKeyQuad('Y')},
		{'Z', bufferKeyQuad('Z')},
	};
	

	KeyBuffer buffer = initBuffer(10);
	GLuint vao = bufferKeyQuad(buffer.queue[0]);

	int peekSize = 5;
	std::vector<char> next = peekKeys(buffer, peekSize);

	int score = 0;
	int hp = 3;
	
	char lastKey = 0;

	while (!glfwWindowShouldClose(window)) {
		char keyStroke = getKeyStroke(window);

		if (glfwGetKey(window, lastKey) != GLFW_PRESS) {
			processKeyStroke(buffer, keyStroke, score, hp);
			next = peekKeys(buffer, peekSize);
		
			if (hp <= 0) {
				std::cout << "Game Over" << "\n";
				std::cout << "Final Score: " << score << "\n";
				break;
			}
		}

		lastKey = keyStroke;

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
		renderKeyQuad(program, allKeyQuads[next[0]]);
		
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;


	/*int score = 0;
	int hp = 3;

	KeyBuffer buffer = initBuffer(10);

	int preSize = 5;
	std::vector<char> next = peekKeys(buffer, preSize);

	while (true) {
		for (int i = 0; i < size(next); i++) {
			if (i != size(next) - 1) {
				std::cout << next[i] << "  >>  ";
			}
			else {
				std::cout << next[i] << "\n";
			}
		}

		char keyStroke;
		std::cin >> keyStroke;

		if (processKeyStroke(buffer, keyStroke)) {
			score++;
			next = peekKeys(buffer, preSize);
		}
		else {
			hp--;
			std::cout << "Wrong" << "\n";
		}

		if (hp <= 0) {
			std::cout << "Game Over" << "\n";
			std::cout << "Final Score: " << score << "\n";
			break;
		}
	}

	std::cout << "Press Any Key To Close" << "\n";
	char p;
	std::cin >> p;*/
}