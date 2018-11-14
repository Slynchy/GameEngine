#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <engine/Component.h>
#include <engine/Transform.h>

static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		 1.0f,-1.0f, 1.0f
};

// Two UV coordinatesfor each vertex. They were created with Blender.
static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 0.000004f,
	0.000103f, 0.336048f,
	0.335973f, 0.335903f,
	1.000023f, 0.000013f,
	0.667979f, 0.335851f,
	0.999958f, 0.336064f,
	0.667979f, 0.335851f,
	0.336024f, 0.671877f,
	0.667969f, 0.671889f,
	1.000023f, 0.000013f,
	0.668104f, 0.000013f,
	0.667979f, 0.335851f,
	0.000059f, 0.000004f,
	0.335973f, 0.335903f,
	0.336098f, 0.000071f,
	0.667979f, 0.335851f,
	0.335973f, 0.335903f,
	0.336024f, 0.671877f,
	1.000004f, 0.671847f,
	0.999958f, 0.336064f,
	0.667979f, 0.335851f,
	0.668104f, 0.000013f,
	0.335973f, 0.335903f,
	0.667979f, 0.335851f,
	0.335973f, 0.335903f,
	0.668104f, 0.000013f,
	0.336098f, 0.000071f,
	0.000103f, 0.336048f,
	0.000004f, 0.671870f,
	0.336024f, 0.671877f,
	0.000103f, 0.336048f,
	0.336024f, 0.671877f,
	0.335973f, 0.335903f,
	0.667969f, 0.671889f,
	1.000004f, 0.671847f,
	0.667979f, 0.335851f
};

namespace GameEngine {
	class MeshRenderer : public GameEngine::Component
	{
	private:

			void Init() {

			}

		public:
			GLuint shaderID;
			GLuint vertArrayID;
			GLuint vertBuffer;
			GLuint colorbuffer;
			GLuint uvBuffer;

			GLuint textureID;
			GLuint textureUniID;
			
			glm::mat4 modelMat; 
			GLuint matID;

			MeshRenderer(GLuint shaderID, GLuint texID = 0) {
				this->textureID = texID;
				this->modelMat = glm::mat4(1.0f);

				glGenVertexArrays(1, &this->vertArrayID);
				glBindVertexArray(this->vertArrayID);

				this->shaderID = shaderID;
				this->matID = glGetUniformLocation(this->shaderID, "MVP");
				textureUniID = glGetUniformLocation(this->shaderID, "myTextureSampler");

				// gen
				glGenBuffers(1, &this->vertBuffer);
				// bind
				glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
				// give to ogl
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

				glGenBuffers(1, &uvBuffer);
				glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

				//glBindVertexArray(0);
			}

			void Update(float delta, glm::mat4 projection, glm::mat4 view, glm::vec3 offset = glm::vec3(0.0f)) {
				auto test = this->GetParent()->GetComponent<Transform>();
				auto trans = test->getTranslationMatrix() + glm::translate(offset);
				auto rot = test->getRotationMatrix();
				auto scale = test->getScaleMatrix();
				glm::mat4 mvp = projection * view * (trans * rot * scale);

				glUseProgram(this->shaderID);
				glUniformMatrix4fv(matID, 1, GL_FALSE, &mvp[0][0]);

				// Bind our texture in Texture Unit 0
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, this->textureID);
				// Set our "myTextureSampler" sampler to use Texture Unit 0
				glUniform1i(this->textureUniID, 0);

				// 1rst attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
				glVertexAttribPointer(
					0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);

				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					2,                                // size : U+V => 2
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);

				// Draw the cube !
				glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
	};
}