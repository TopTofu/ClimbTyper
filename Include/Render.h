#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void initOpenGL(GLFWwindow* window, int window_width, int window_height);
void renderKeyQuad(GLuint shader, GLuint vao);