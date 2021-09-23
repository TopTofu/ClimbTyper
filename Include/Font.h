#pragma once

#include <map>
#include <fstream>
#include <glad/glad.h>
#include <vector>
#include <stb/stb_image.h>
#include <GLFW/glfw3.h>


#define BITMAP_WIDTH		1024.0f
#define BITMAP_HEIGHT		1024.0f
#define CELL_WIDTH			64.0f
#define CELL_HEIGHT			64.0f
#define CELLS_PER_ROW		8.0f
#define CELLS_PER_COLLUMN	8.0f

GLuint loadFontFileIntoTexture(const char* path);
GLuint bufferKeyQuad(char c);
char getKeyStroke(GLFWwindow* window);
