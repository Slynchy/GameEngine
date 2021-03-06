

#include "Mesh.h"
#include <engine/Entity.h>
#include <engine/Transform.h>

GameEngine::Mesh::Mesh() {
	glGenVertexArrays(1, &vertArrayID);
	glGenBuffers(1, &uvBuffer);
	glGenBuffers(1, &vertBuffer);
};

void GameEngine::Mesh::Init(std::vector<GLfloat> vertex_buffer_data, std::vector<GLfloat> uv_buffer_data) {
	glBindVertexArray(this->vertArrayID);
	glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_buffer_data.size(), &vertex_buffer_data.at(0), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uv_buffer_data.size(), &uv_buffer_data.at(0), GL_STATIC_DRAW);

	glBindVertexArray(0);
}