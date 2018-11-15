#pragma once

#include <GL/glew.h>
#include <GL/GL.h>
#include <string>
#include <map>
#include <vector>
#include <engine/Sound.h>
#include <engine/Texture.h>
#include <fstream>
#include <sstream>

namespace GameEngine {

	class ResourceManager
	{
	private:
		std::map<std::string, Texture*> m_loadedTextures;
		std::map<std::string, GLuint> m_loadedShaders; // todo: wrap shader uint as object
		std::map<std::string, Sound*> m_loadedAudio;

	public:
		ResourceManager() {

		};

		void UnloadTexture(std::string _id) {
			// TODO: implement
		}

		bool LoadShaders(const char* _id, const char * vertex_file_path, const char * fragment_file_path) {

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
				return false;
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
			else {
				return false;
			}

			GLint res = GL_FALSE;
			GLint logLen;

			printf("Compiling shader %s...\n", vertex_file_path);
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
				return false;
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
				return false;
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
				return false;
			}

			glDetachShader(PID, vShaderID);
			glDetachShader(PID, fShaderID);

			glDeleteShader(vShaderID);
			glDeleteShader(fShaderID);

			printf("Finished compiling shader program\n");

			this->m_loadedShaders.insert(std::pair<std::string, GLuint>(_id, PID));

			return true;
		}

		GLuint GetShader(std::string _id) {
			if (m_loadedShaders.find(_id) == m_loadedShaders.end()) {
				return 0;
			}
			else {
				return m_loadedShaders.at(_id);
			}
		}

		std::string LoadTexture(std::string _path) {
			Texture* temp = new Texture(_path);
			this->m_loadedTextures.insert(std::pair<std::string, Texture*>(_path, temp));
			return _path;
		}

		Texture* GetTexture(std::string _id) {
			if (m_loadedTextures.find(_id) == m_loadedTextures.end()) {
				return nullptr;
			}
			else {
				return m_loadedTextures.at(_id);
			}
		}

		std::string LoadSound(const char* path) {
			Sound* snd = new Sound(path);
			this->m_loadedAudio.insert(std::pair<std::string, Sound*>(path, snd));
			return std::string(path);
		}

		Sound* GetSound(std::string _id) {
			if (m_loadedAudio.find(_id) == m_loadedAudio.end()) {
				return nullptr;
			}
			else {
				return m_loadedAudio.at(_id);
			}
		}

		~ResourceManager() {

		};
	};

}
