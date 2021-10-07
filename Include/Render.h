#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <Camera.h>
#include "../Source/Variables.cpp"
#include <KeyGenerator.h>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
};

struct Mesh {
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	int primitve = GL_TRIANGLES;
	GLuint vao;

	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
};


void initOpenGL(GLFWwindow* window, int window_width, int window_height);
void renderKeyQuad(GLuint shader, KeyPrompt key, GLuint texture, GLuint vao);
Mesh getCircleMesh(float r, int numSegments);
Mesh getQuadMesh(float mX, float mY, float w, float h);
void bufferMesh(Mesh& mesh);
void renderMesh(Mesh& mesh, GLuint shader, Camera& camera);
