#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <engine/Component.h>
#include <engine/Transform.h>

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
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

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
};

namespace GameEngine {
	class MeshRenderer : public GameEngine::Component
	{
	private:
			GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path) {

				// Create the shaders
				GLuint vShaderID = glCreateShader(GL_VERTEX_SHADER);
				GLuint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);

				// Read the Vertex Shader code from the file
				std::string vShaderCode;
				std::ifstream vShaderIStream(vertex_file_path, std::ios::in);
				if (vShaderIStream.is_open()) {
					std::stringstream sstream;
					sstream << vShaderIStream.rdbuf();
					vShaderCode = sstream.str();
					vShaderIStream.close();
				}
				else {
					printf("Failed to open %s!!\n", vertex_file_path);
					getchar();
					return 0;
				}

				// Read the Fragment Shader code from the file
				std::string fShaderCode;
				std::ifstream fShaderIStream(fragment_file_path, std::ios::in);
				if (fShaderIStream.is_open()) {
					std::stringstream sstr;
					sstr << fShaderIStream.rdbuf();
					fShaderCode = sstr.str();
					fShaderIStream.close();
				}

				GLint res = GL_FALSE;
				GLint logLen;

				char const *vPointer = vShaderCode.c_str();
				glShaderSource(vShaderID, 1, &vPointer, NULL);
				glCompileShader(vShaderID);

				// Check Vertex Shader
				glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &res);
				glGetShaderiv(vShaderID, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0) {
					std::vector<char> vShaderError(logLen + 1);
					glGetShaderInfoLog(vShaderID, logLen, NULL, &vShaderError[0]);
					printf("%s\n", &vShaderError[0]);
				}

				// Compile Fragment Shader
				printf("Compiling shader %s...\n", fragment_file_path);
				char const * fPointer = fShaderCode.c_str();
				glShaderSource(fShaderID, 1, &fPointer, NULL);
				glCompileShader(fShaderID);

				// Check Fragment Shader
				glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &res);
				glGetShaderiv(fShaderID, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0) {
					std::vector<char> fShaderError(logLen + 1);
					glGetShaderInfoLog(fShaderID, logLen, NULL, &fShaderError[0]);
					printf("%s\n", &fShaderError[0]);
				}

				// Link the program
				printf("Linking shader program...\n");
				GLuint PID = glCreateProgram();
				glAttachShader(PID, vShaderID);
				glAttachShader(PID, fShaderID);
				glLinkProgram(PID);

				// Check the program
				glGetProgramiv(PID, GL_LINK_STATUS, &res);
				glGetProgramiv(PID, GL_INFO_LOG_LENGTH, &logLen);
				if (logLen > 0) {
					std::vector<char> ProgramErrorMessage(logLen + 1);
					glGetProgramInfoLog(PID, logLen, NULL, &ProgramErrorMessage[0]);
					printf("%s\n", &ProgramErrorMessage[0]);
				}

				glDetachShader(PID, vShaderID);
				glDetachShader(PID, fShaderID);

				glDeleteShader(vShaderID);
				glDeleteShader(fShaderID);

				printf("Finished compiling shader program\n");
				return PID;
			}

		public:
			GLuint shaderID;
			GLuint vertArrayID;
			GLuint vertBuffer;
			GLuint colorbuffer;
			glm::mat4 modelMat; 
			GLuint matID;

			MeshRenderer(std::string vShaderPath = "shaders/vert.glsl", std::string fShaderPath = "shaders/frag.glsl") {
				glGenVertexArrays(1, &this->vertArrayID);
				glBindVertexArray(this->vertArrayID);

				this->modelMat = glm::mat4(1.0f);

				this->shaderID = this->LoadShaders(vShaderPath.c_str(), fShaderPath.c_str());
				this->matID = glGetUniformLocation(this->shaderID, "MVP");

				// gen
				glGenBuffers(1, &this->vertBuffer);
				// bind
				glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
				// give to ogl
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

				glGenBuffers(1, &this->colorbuffer);
				glBindBuffer(GL_ARRAY_BUFFER, this->colorbuffer);
				glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
			}

			void Update(glm::mat4 projection, glm::mat4 view) {
				auto test = this->GetParent()->GetComponent<Transform>();
				auto trans = test->getTranslationMatrix();
				auto rot = test->getRotationMatrix();
				auto scale = test->getScaleMatrix();
				glm::mat4 mvp = projection * view * (trans * rot * scale);
				glUniformMatrix4fv(matID, 1, GL_FALSE, &mvp[0][0]);

				glUseProgram(this->shaderID);
				// 1st attribute buffer : vertices
				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, this->vertBuffer);
				glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);
				// 2nd attribute buffer : colors
				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);
				// Draw the cube !
				glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares
				glDisableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
	};
}