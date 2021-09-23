#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>

std::string readFileContents(const char* filePath);
std::string getExtension(const char* filePath);
GLuint compileShader(const char* filePath);
GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);