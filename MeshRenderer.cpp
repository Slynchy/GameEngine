#include "MeshRenderer.h"
#include <GL/glew.h>
#include <engine/Entity.h>
#include <tiny_obj_loader.h>

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

	for (Mesh mesh : m_meshes) {

		glBindVertexArray(mesh.vertArrayID);
		glUseProgram(this->shaderID);
		glUniformMatrix4fv(matID, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		glUniform1i(this->textureUniID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertBuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.uvBuffer);
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

void GameEngine::MeshRenderer::InitFromOBJ(std::string _filename) {
	std::string inputfile = _filename;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	std::string warn; 
	
	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str())) {
		printf("Something went wrong when loading OBJ file %s \n", _filename.c_str());
		if (!err.empty()) {
			printf(err.c_str());
		}
		return;
	}

	// todo: replace with proper logging
	if (!err.empty()) { 
		printf(err.c_str());
		// should be a warning; we already check retval from LoadObj
	}

	for (size_t s = 0; s < shapes.size(); s++) {
		size_t index_offset = 0;

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
			size_t fv = shapes[s].mesh.num_face_vertices[f];
			std::vector<tinyobj::real_t> vert;
			std::vector<tinyobj::real_t> uv;

			for (size_t v = 0; v < fv; v++) {

				tinyobj::index_t ind = shapes[s].mesh.indices[index_offset + v];

				vert.push_back(attrib.vertices[3 * ind.vertex_index + 0]);
				vert.push_back(attrib.vertices[3 * ind.vertex_index + 1]);
				vert.push_back(attrib.vertices[3 * ind.vertex_index + 2]);

				uv.push_back(attrib.texcoords[2 * ind.texcoord_index + 0]);
				uv.push_back(attrib.texcoords[2 * ind.texcoord_index + 1]);

				// normals
					//tinyobj::real_t nx = attrib.normals[3 * ind.normal_index + 0];
					//tinyobj::real_t ny = attrib.normals[3 * ind.normal_index + 1];
					//tinyobj::real_t nz = attrib.normals[3 * ind.normal_index + 2];

				// colors 
					// tinyobj::real_t r = attrib.colors[3*ind.vertex_index+0];
					// tinyobj::real_t g = attrib.colors[3*ind.vertex_index+1];
					// tinyobj::real_t b = attrib.colors[3*ind.vertex_index+2];
			}
			index_offset += fv;
			Mesh mesh;
			mesh.Init(vert, uv);
			this->AddMesh(mesh);
		}
	}
}