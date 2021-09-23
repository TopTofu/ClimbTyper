#include <Render.h>

void initOpenGL(GLFWwindow* window, int window_width, int window_height) {
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, window_width, window_height);

	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	//glProvokingVertex(GL_FIRST_VERTEX_CONVENTION);

	// vsync
	glfwSwapInterval(0);
}

void renderKeyQuad(GLuint shader, GLuint vao) {
	glUseProgram(shader);

	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

