#pragma once

#include <GL/glew.h>
#include "VertexArrayObject.h"

namespace GameEngine {

	class Mesh
	{
		private:
			//VertexArrayObject VAO;
		protected:
		public:

			GLuint vertArrayID;
			GLuint vertBuffer;
			GLuint colorbuffer;
			GLuint uvBuffer;

			Mesh() {
				glGenVertexArrays(1, &vertArrayID);
				glGenBuffers(1, &uvBuffer);
				glGenBuffers(1, &vertBuffer);
			};

			void Init(std::vector<GLfloat> vertex_buffer_data, std::vector<GLfloat> uv_buffer_data) {
				glBindVertexArray(this->vertArrayID);
				// gen
				// bind
				glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
				// give to ogl
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertex_buffer_data.size(), &vertex_buffer_data.at(0), GL_STATIC_DRAW);

				glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uv_buffer_data.size(), &uv_buffer_data.at(0), GL_STATIC_DRAW);

				glBindVertexArray(0);
			}

			~Mesh() {};


	};

}