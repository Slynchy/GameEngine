#pragma once

#include <GL/glew.h>
#include <engine/Component.h>
#include <stdint.h>
#include <engine/Shader.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/types.h>
#include <glm/gtc/matrix_transform.hpp>
#define INVALID_MATERIAL 0xFFFFFFFF


namespace GameEngine {

	class Transform; 
	
	struct Vertex
	{
		// Position
		glm::vec3 Position;
		// Normal
		glm::vec3 Normal;
		// TexCoords
		glm::vec2 TexCoords;
	};

	struct Texture
	{
		GLuint id;
		std::string type;
		aiString path;
	};

	class Mesh : public GameEngine::Component
	{
	public:
		/*  Mesh Data  */
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

		/*  Functions  */
		// Constructor
		Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
		{
			this->vertices = vertices;
			this->indices = indices;
			this->textures = textures;

			// Now that we have all the required data, set the vertex buffers and its attribute pointers.
			this->setupMesh();
		}

		// Render the mesh
		void Render(Shader* shader)
		{
			// Bind appropriate textures
			GLuint diffuseNr = 1;
			GLuint specularNr = 1;

			for (GLuint i = 0; i < this->textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
				// Retrieve texture number (the N in diffuse_textureN)
				std::stringstream ss;
				std::string number;
				std::string name = this->textures[i].type;

				if (name == "texture_diffuse")
				{
					ss << diffuseNr++; // Transfer GLuint to stream
				}
				else if (name == "texture_specular")
				{
					ss << specularNr++; // Transfer GLuint to stream
				}

				number = ss.str();
				// Now set the sampler to the correct texture unit
				glUniform1i(glGetUniformLocation(shader->shaderProgram, (name + number).c_str()), i);
				// And finally bind the texture
				glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
			}

			// Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
			glUniform1f(glGetUniformLocation(shader->shaderProgram, "material.shininess"), 16.0f);

			// Draw mesh
			glBindVertexArray(this->VAO);
			glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			// Always good practice to set everything back to defaults once configured.
			for (GLuint i = 0; i < this->textures.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, 0);
			}
		}

		void Update(glm::mat4 projection, glm::mat4 view) {

		}

	private:
		/*  Render data  */
		GLuint VAO, VBO, EBO;

		/*  Functions    */
		// Initializes all the buffer objects/arrays
		void setupMesh()
		{
			// Create buffers/arrays
			glGenVertexArrays(1, &this->VAO);
			glGenBuffers(1, &this->VBO);
			glGenBuffers(1, &this->EBO);

			glBindVertexArray(this->VAO);
			// Load data into vertex buffers
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			// A great thing about structs is that their memory layout is sequential for all its items.
			// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
			// again translates to 3/2 floats which translates to a byte array.
			glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

			// Set the vertex attribute pointers
			// Vertex Positions
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
			// Vertex Normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, Normal));
			// Vertex Texture Coords
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, TexCoords));

			glBindVertexArray(0);
		}
	};


	/*class Mesh : public GameEngine::Component {
		private:

			Transform* m_transform;

			GLuint vbo[2], vao[1];
			std::vector<GLfloat> positions;
			std::vector<GLfloat> colors;
			Shader* shader;
			glm::mat4 model;
			uint32_t positionAttributeIndex = (0);
			uint32_t colorAttributeIndex = (1);

			static std::vector<GLfloat> ReadFile(const char* file);

			void Render();
			void ResetMatrix();
			void Translate(const glm::vec3 &axis);

			// Cleanup all the things we bound and allocated
			void CleanUp();

			// This is where we setup the model like we saw in the first part
			bool SetupBufferObjects();

			void SetShader(Shader* _shader);

			void Init();

		protected:
		public:
			Mesh(Shader* _shader) {
				shader = _shader;
				model = glm::mat4(1.0);
				SetupBufferObjects();
			};

			void Update();

			glm::mat4 GetModel();

			void SetMatrix(glm::mat4 mvp);
	};*/
}