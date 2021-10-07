#include <Render.h>


void initOpenGL(GLFWwindow* window, int width, int height) {
	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, width, height);

	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	// vsync
	glfwSwapInterval(0);
}

void renderKeyQuad(GLuint shader, KeyPrompt key, GLuint texture, GLuint vao) {
	glBindTexture(GL_TEXTURE_2D, texture);

	glUseProgram(shader);

	glBindVertexArray(vao);

	glm::mat4 transl = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	transl = glm::translate(transl, key.translation);
	rot = glm::mat4_cast(key.rotation);
	sca = glm::scale(sca, key.scale);

	// this is probably slower than multiplying in shader
	glm::mat4 transform = transl * rot * sca;

	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, glm::value_ptr(getProjectionMatrix(WINDOW_WIDTH, WINDOW_HEIGHT)));
	glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}


Mesh getCircleMesh(float r, int numSegments) {
	Mesh mesh = {};
	for (int i = 0; i < numSegments; i++) {
		float theta = 2.0f * 3.14159f * float(i) / float(numSegments);

		float x = r * cosf(theta);
		float y = r * sinf(theta);

		Vertex v = { glm::vec3(x, y, 0), glm::vec2(0, 0) };
		mesh.vertices.push_back(v);

		mesh.indices.push_back(i);
	}

	mesh.primitve = GL_LINE_LOOP;

	return mesh;
}


Mesh getQuadMesh(float mX, float mY, float w, float h) {
	Mesh mesh;
	float halfW = w / 2.0f;
	float halfH = h / 2.0f;

	Vertex v0 = { glm::vec3(mX - halfW, mY - halfH, 0), glm::vec2(0, 0) };
	Vertex v1 = { glm::vec3(mX + halfW, mY - halfH, 0), glm::vec2(0, 0) };
	Vertex v2 = { glm::vec3(mX + halfW, mY + halfH, 0), glm::vec2(0, 0) };
	Vertex v3 = { glm::vec3(mX - halfW, mY + halfH, 0), glm::vec2(0, 0) };

	mesh.vertices.push_back(v0);
	mesh.vertices.push_back(v1);
	mesh.vertices.push_back(v2);
	mesh.vertices.push_back(v3);

	mesh.indices.push_back(0);
	mesh.indices.push_back(1);
	mesh.indices.push_back(2);

	mesh.indices.push_back(0);
	mesh.indices.push_back(2);
	mesh.indices.push_back(3);

	mesh.primitve = GL_TRIANGLES;

	return mesh;
}


void bufferMesh(Mesh& mesh) {
	GLuint vao, vbo, ebo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ARRAY_BUFFER, mesh.vertices.size() * sizeof(Vertex), mesh.vertices.data(), GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), mesh.indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);

	mesh.vao = vao;
}


void renderMesh(Mesh& mesh, GLuint shader, Camera& camera) {
	glUseProgram(shader);

	glBindVertexArray(mesh.vao);

	glm::mat4 cameraMatrix = getCameraMatrix(camera);
	glUniformMatrix4fv(glGetUniformLocation(shader, "camera"), 1, GL_FALSE, glm::value_ptr(cameraMatrix));

	glm::mat4 transl = glm::mat4(1.0f);
	glm::mat4 rot = glm::mat4(1.0f);
	glm::mat4 sca = glm::mat4(1.0f);

	transl = glm::translate(transl, mesh.translation);
	rot = glm::mat4_cast(mesh.rotation);
	sca = glm::scale(sca, mesh.scale);

	// this is probably slower than multiplying in shader
	glm::mat4 transform = transl * rot * sca;

	glUniformMatrix4fv(glGetUniformLocation(shader, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

	glDrawElements(mesh.primitve, mesh.indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

