#include "MeshRenderer.h"
#include <GL/glew.h>
#include <engine/Entity.h>

glm::mat4 GameEngine::MeshRenderer::getMVP(glm::mat4 projection, glm::mat4 view, glm::vec3 offset) {
	Transform* test = this->GetParent()->GetComponent<Transform>();
	glm::mat4 trans = test->getTranslationMatrix() + glm::translate(offset);
	glm::mat4 rot = test->getRotationMatrix();
	glm::mat4 scale = test->getScaleMatrix();
	return projection * view * (trans * rot * scale);
}

GameEngine::MeshRenderer::MeshRenderer(GLuint shaderID, GLuint texID) {
	this->textureID = texID;
	this->modelMat = glm::mat4(1.0f);

	this->shaderID = shaderID;
	this->matID = glGetUniformLocation(this->shaderID, "MVP");
	textureUniID = glGetUniformLocation(this->shaderID, "textureSampler");
}

void GameEngine::MeshRenderer::Draw(glm::mat4 projection, glm::mat4 view, glm::vec3 offset) {
	glm::mat4 mvp = getMVP(projection, view, offset);

	for (Mesh* mesh : m_meshes) {

		glBindVertexArray(mesh->vertArrayID);
		glUseProgram(this->shaderID);
		glUniformMatrix4fv(matID, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glUniform1i(this->textureUniID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertBuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mesh->uvBuffer);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // todo: fixme
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glBindVertexArray(0);

	}
}

/// @deprecated moved to Model.h/cpp
void GameEngine::MeshRenderer::InitFromOBJ(std::string _filename) {
}