#include <glad/glad.h>
#include <iostream>
#include <glm/glm.hpp>
#include <queue>

#define STB_IMAGE_IMPLEMENTATION

#include "KeyGenerator.h"
#include "Window.h"
#include "Render.h"
#include "Font.h"
#include "Shader.h"
#include "Camera.h"
#include "Source/Variables.cpp"
#include <Wall.h>
#include "Climber.h"

int main() {

	GLFWwindow* window = initWindow(WINDOW_WIDTH, WINDOW_HEIGHT);
	initOpenGL(window, WINDOW_WIDTH, WINDOW_HEIGHT);

	GLuint texture = loadFontFileIntoTexture("E:/ClimbTyper/Resources/fontAtlasBig.png");

	GLuint vertex = compileShader("E:/ClimbTyper/Resources/Shader/default.vert");
	GLuint fragment = compileShader("E:/ClimbTyper/Resources/Shader/default.frag");

	GLuint shader = createProgram(vertex, fragment);

	glUseProgram(shader);

	const std::map<char, GLuint> allKeyQuads = {
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

	int score = 0;
	int hp = 3;

	char lastKey = 0;
	int frameCount = 0;

	glm::vec3 initalCamPos = glm::vec3{ 0.0f, 0.45f, 1.0f };
	Camera c = initCamera(initalCamPos);

	Wall wall = initWall();

	Climber climber = initClimber(glm::vec3(0.0f, 0.6f, 0.0f));
	findStartingPos(climber, wall);

	while (!glfwWindowShouldClose(window)) {
		frameCount++;

		glClearColor(10 / 255.0f, 57 / 255.0f, 47 / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		{
			char keyStroke = getKeyStroke(window);

			if (glfwGetKey(window, lastKey) != GLFW_PRESS) {
				if (processKeyStroke(wall, climber, keyStroke, score, hp)) {
					printf("Score: %i\n", score);
					//c.position.y += 0.1f;
				}
			}
			lastKey = keyStroke;

			/*if (hp <= 0) {
				std::cout << "Game Over" << "\n";
				std::cout << "Final Score: " << score << "\n";
				break;
			}*/
		}


		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
			c.position = initalCamPos;
			wall = initWall();
			resetClimberPos(climber);
			findStartingPos(climber, wall);
		}

		/*if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
			balanceClimberBody(climber);
		}*/

		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
			c.position.y += -0.001f;
		}
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
			c.position.y += 0.001f;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			c.position.x += 0.001f;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			c.position.x -= 0.001f;
		}

		renderWall(wall, shader, allKeyQuads, texture, c);

		renderClimber(climber, shader, c);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}